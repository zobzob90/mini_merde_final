/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:58 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/24 17:53:55 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if a command string matches a recognized built-in command;
returns TRUE or FALSE.*/

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "michel") == 0
		|| ft_strcmp(cmd, "jacquie") == 0 || ft_strcmp(cmd, "hell") == 0
		|| ft_strcmp(cmd, "merde") == 0 || ft_strcmp(cmd, "res") == 0
		|| ft_strcmp(cmd, "sudo") == 0 || ft_strcmp(cmd, "moulinette") == 0
		|| ft_strcmp(cmd, "miaou") == 0 || ft_strcmp(cmd, "Xavier") == 0
		||ft_strcmp(cmd, ":") == 0 || ft_strcmp(cmd, "!") == 0
		||ft_strcmp(cmd, "kevin") == 0)
		return (TRUE);
	else
		return (FALSE);
}

/*Restores standard input and output file descriptors from backups,
closing backups afterwards.*/

static void	reset_stdio(t_shell *shell)
{
	if (shell->fd_in != -1)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
	}
	if (shell->fd_out != -1)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
	}
}

/*Executes a built-in command in the parent process
with redirection handling and restores stdio.*/

int	exec_builtin_parent(t_cmd *cmd, t_shell *shell)
{
	int	ret;

	shell->fd_in = dup(STDIN_FILENO);
	if (shell->fd_in == -1)
		return (perror("dup stdin"), 1);
	shell->fd_out = dup(STDOUT_FILENO);
	if (shell->fd_out == -1)
	{
		close (shell->fd_in);
		return (perror("dup stdout"), 1);
	}
	if (handle_redir_exec(cmd->redir) != 0)
	{
		reset_stdio(shell);
		shell->exit_code = 1;
		return (1);
	}
	ret = launch_built(shell, cmd->cmds, cmd);
	reset_stdio(shell);
	shell->exit_code = ret;
	return (ret);
}
