/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:30 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/27 13:41:31 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Manage parent process file descriptors after forking a child.*/

int	handle_parent(pid_t pid, t_cmd *cmd, int *pipefd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next_non_empty_cmd(cmd))
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	set_signal_handlers();
	return (pid);
}

/*Update shell exit code based on child process termination status.*/

int	update_exit_code(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
	else
		shell->exit_code = 1;
	return (shell->exit_code);
}

/*Clean the heredoc and update the exit code to 1.*/

static int	heredoc_fail(t_shell *shell)
{
	cleanup_heredocs(shell->cmd);
	shell->exit_code = 1;
	return (1);
}

static int	handle_empty_single_node(t_shell *shell)
{
	shell->exit_code = 127;
	printf(": command not found\n");
	return (0);
}

static int	handle_redir_only_cmd(t_cmd *cmd, t_shell *shell, int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	exec_redir_only(cmd, shell, *prev_fd);
	return (1);
}

static int	handle_builtin_cmd(t_cmd *cmd, t_shell *shell, int *prev_fd)
{
	int	ret;

	ret = try_exec_builtin(cmd, shell);
	if (ret != -1)
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		shell->exit_code = ret;
		return (ret);
	}
	return (-1);
}

static int	process_cmd_node(t_cmd *cmd, t_shell *shell,
		int *prev_fd, pid_t *pid)
{
	int	ret;

	if (is_empty_node(cmd))
	{
		if (!cmd->next && !cmd->prev)
			return (handle_empty_single_node(shell));
		return (1);
	}
	if ((!cmd->cmds || !cmd->cmds[0]) && cmd->redir)
		return (handle_redir_only_cmd(cmd, shell, prev_fd));
	ret = handle_builtin_cmd(cmd, shell, prev_fd);
	if (ret != -1)
		return (ret);
	if (exec_external_cmd(cmd, shell, prev_fd, pid) != 0)
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		return (-1);
	}
	return (0);
}

static int	handle_cmd_result(int ret, t_cmd **cmd,
	int *has_real_commands, int *i)
{
	if (ret > 0)
		return (ret);
	if (ret == -1)
		return (-1);
	if (ret == 1)
	{
		*cmd = (*cmd)->next;
		return (0);
	}
	*has_real_commands = 1;
	(*i)++;
	*cmd = (*cmd)->next;
	return (0);
}

static int	finalize_pipeline(int prev_fd, int has_real_commands,
	int i, t_shell *shell)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (!has_real_commands && i == 0)
	{
		shell->exit_code = 0;
		return (0);
	}
	return (i);
}

static int	launch_pipeline(t_shell *shell, t_cmd *cmd, pid_t *pids)
{
	int		prev_fd;
	int		i;
	int		ret;
	int		has_real_commands;

	prev_fd = -1;
	i = 0;
	has_real_commands = 0;
	while (cmd)
	{
		pids[i] = 0;
		ret = process_cmd_node(cmd, shell, &prev_fd, &(pids[i]));
		ret = handle_cmd_result(ret, &cmd, &has_real_commands, &i);
		if (ret != 0)
			return (ret);
		if (ret == 0 && cmd == NULL)
			break ;
	}
	return (finalize_pipeline(prev_fd, has_real_commands, i, shell));
}

/*Main fonction of the exec.*/

int	exec_cmds(t_shell *shell, t_cmd *cmd)
{
	pid_t	pids[MAX_PIPE];
	int		j;
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (setup_heredocs(cmd, shell) != 0)
		return (heredoc_fail(shell));
	i = launch_pipeline(shell, cmd, pids);
	if (i < 0)
		return (-1);
	if (i == 0 || (i == 1 && pids[0] == 0))
		return (shell->exit_code);
	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		j++;
	}
	update_exit_code(shell, status);
	cleanup_heredocs(shell->cmd);
	return (shell->exit_code);
}
