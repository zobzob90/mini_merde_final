/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:47:30 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/30 08:48:51 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_empty_single_node(t_shell *shell)
{
	shell->exit_code = 127;
	printf(": command not found\n");
	return (0);
}

int	handle_redir_only_cmd(t_cmd *cmd, t_shell *shell, int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	exec_redir_only(cmd, shell, *prev_fd);
	return (1);
}

int	handle_builtin_cmd(t_cmd *cmd, t_shell *shell, int *prev_fd)
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

int	process_cmd_node(t_cmd *cmd, t_shell *shell,
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
