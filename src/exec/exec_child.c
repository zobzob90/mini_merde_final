/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:30:12 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/12 13:41:22 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Check is there an infile redirection in the command*/

int	has_infile_redir(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			return (1);
		redir = redir->next;
	}
	return (0);
}

/*Main exec for child processes*/

void	exec_child(t_cmd *cmd, t_shell *shell, int prev_fd, int pipefd[2])
{
	int	ret;

	if (prev_fd != -1 && !has_infile_redir(cmd))
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			(perror("dup2 prev_fd"), exit(1));
		close (prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			(perror("dup2 pipefd[1]"), exit(1));
		close(pipefd[1]);
	}
	if (handle_redir_exec(cmd->redir))
		exit(1);
	if (!cmd->cmds || !cmd->cmds[0])
		exit(0);
	if (is_builtin(cmd->cmds[0]))
	{
		ret = launch_built(shell, cmd->cmds, cmd);
		exit (ret);
	}
	(exec_external(cmd, shell->env), exit(127));
}
