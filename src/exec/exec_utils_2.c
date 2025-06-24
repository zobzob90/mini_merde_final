/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:20:39 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/24 16:59:04 by ertrigna         ###   ########.fr       */
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
