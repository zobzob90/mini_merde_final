/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:30 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/23 18:09:21 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Manage parent process file descriptors after forking a child.*/

int	handle_parent(pid_t pid, t_cmd *cmd, int *pipefd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	waitpid(pid, NULL, 0);
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

/*Wait the children and clean the heredocs.*/

static int	finalize_execution(t_shell *shell, pid_t last_pid)
{
	int	status;

	status = 0;
	if (last_pid)
	{
		waitpid(last_pid, &status, 0);
		update_exit_code(shell, status);
	}
	cleanup_heredocs(shell->cmd);
	return (shell->exit_code);
}

/*Main fonction of the exec.*/

int	exec_cmds(t_shell *shell, t_cmd *cmd)
{
	int		prev_fd;
	pid_t	last_pid;
	int		ret;

	prev_fd = -1;
	last_pid = 0;
	if (setup_heredocs(cmd, shell) != 0)
		return (heredoc_fail(shell));
	while (cmd)
	{
		if (skip_empty_node(&cmd))
			continue ;
		if ((!cmd->cmds || !cmd->cmds[0]) && cmd->redir)
		{
			(exec_redir_only(cmd, shell, prev_fd), cmd = cmd->next);
			continue ;
		}
		ret = try_exec_builtin(cmd, shell);
		if (ret != -1)
			return (ret);
		if (exec_external_cmd(cmd, shell, &prev_fd, &last_pid) != 0)
			return (-1);
		cmd = cmd->next;
	}
	return (finalize_execution(shell, last_pid));
}
