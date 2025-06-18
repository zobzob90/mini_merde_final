/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:58 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/12 11:31:36 by ertrigna         ###   ########.fr       */
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
		||ft_strcmp(cmd, ":") == 0 || ft_strcmp(cmd, "!") == 0)
		return (TRUE);
	else
		return (FALSE);
}

/*Restores standard input and output file descriptors from backups,
closing backups afterwards.*/

static void	reset_stdio(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

/*Executes a built-in command in the parent process
with redirection handling and restores stdio.*/

int	exec_builtin_parent(t_cmd *cmd, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		return (perror("dup stdin"), 1);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
	{
		close (stdin_backup);
		return (perror("dup stdout"), 1);
	}
	if (handle_redir_exec(cmd->redir) != 0)
	{
		reset_stdio(stdin_backup, stdout_backup);
		g_last_exit_code = 1;
		return (1);
	}
	ret = launch_built(shell, cmd->cmds, cmd);
	reset_stdio(stdin_backup, stdout_backup);
	g_last_exit_code = ret;
	return (ret);
}
