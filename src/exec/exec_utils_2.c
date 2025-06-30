/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:20:39 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/30 08:46:16 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->cmds || !cmd->cmds[0])
		return (-1);
	if (is_builtin(cmd->cmds[0]) && !cmd->next && !cmd->prev)
		return (exec_builtin_parent(cmd, shell));
	return (-1);
}

int	skip_empty_node(t_cmd **cmd)
{
	if ((!(*cmd)->cmds || !(*cmd)->cmds[0]) && !(*cmd)->redir)
	{
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}

int	is_empty_node(t_cmd *cmd)
{
	if (!cmd->cmds || !cmd->cmds[0]
		|| (cmd->cmds[0] && ft_strlen(cmd->cmds[0]) == 0))
	{
		if (!cmd->redir)
			return (1);
	}
	return (0);
}

int	has_next_non_empty_cmd(t_cmd *cmd)
{
	t_cmd	*next_cmd;

	next_cmd = cmd->next;
	while (next_cmd)
	{
		if (!is_empty_node(next_cmd))
			return (1);
		next_cmd = next_cmd->next;
	}
	return (0);
}

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
