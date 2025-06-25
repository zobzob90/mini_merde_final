/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:30 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/25 18:26:44 by ertrigna         ###   ########.fr       */
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

static int	handle_builtin_return(t_shell *shell, int ret)
{
    shell->exit_code = ret;
    return (ret);
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
		if (is_empty_node(cmd))
		{
			if (!cmd->next && !cmd->prev)
			{
				shell->exit_code = 127;
				printf(": command not found\n");
				return (0);
			}
			cmd = cmd->next;
			continue ;
		}
		has_real_commands = 1;
		if ((!cmd->cmds || !cmd->cmds[0]) && cmd->redir)
		{
			if (prev_fd != -1)
			{
				close(prev_fd);
				prev_fd = -1;
			}
			(exec_redir_only(cmd, shell, prev_fd), cmd = cmd->next);
			continue ;
		}
		ret = try_exec_builtin(cmd, shell);
		if (ret != -1)
		{
			if (prev_fd != -1)
				close(prev_fd);
			return (handle_builtin_return(shell, ret));
		}
		if (exec_external_cmd(cmd, shell, &prev_fd, &(pids[i])) != 0)
		{
			if (prev_fd != -1)
				close(prev_fd);
			return (-1);
		}
		i++;
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	if (!has_real_commands && i == 0)
	{
		shell->exit_code = 0;
		return (0);
	}
	return (i);
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
