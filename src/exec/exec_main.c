/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:30 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/13 17:05:52 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_parent(pid_t pid, t_cmd *cmd, int *pipefd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (pid);
}

int	update_exit_code(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
	else
		shell->exit_code = 1;
	g_last_exit_code = shell->exit_code;
	return (g_last_exit_code);
}

/*Clean the heredoc and update the exit code to 1*/

static int	heredoc_fail(t_shell *shell)
{
	cleanup_heredocs(shell->cmd);
	shell->exit_code = 1;
	return (1);
}

/*Wait the children and clean the heredocs*/

static int	finalize_execution(t_shell *shell, pid_t last_pid)
{
	int	status;

	if (last_pid)
	{
		wait_all_children(last_pid, &status);
		update_exit_code(shell, status);
		g_last_exit_code = shell->exit_code;
	}
	cleanup_heredocs(shell->cmd);
	return (g_last_exit_code);
}

/*Main fonction of the exec*/

int	exec_cmds(t_shell *shell, t_cmd *cmd)
{
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;

	if (setup_heredocs(cmd) != 0)
		return (heredoc_fail(shell));
	prev_fd = -1;
	last_pid = 0;
	while (cmd)
	{
		if (cmd->cmds == NULL || cmd->cmds[0] == NULL)
			return (2);
		if (is_builtin(cmd->cmds[0]) && !cmd->next && !cmd->prev)
			return (exec_builtin_parent(cmd, shell));
		if (cmd->next && pipe(shell->pipe_fd) == -1)
			return (perror("pipe"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			exec_child(cmd, shell, prev_fd, shell->pipe_fd);
		last_pid = handle_parent(pid, cmd, shell->pipe_fd, &prev_fd);
		cmd = cmd->next;
	}

	return (finalize_execution(shell, last_pid));
}
