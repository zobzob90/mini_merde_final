/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:58 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/09 14:21:11 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Check if the command is a builtin*/

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
		|| ft_strcmp(cmd, "miaou") == 0 || ft_strcmp(cmd, "Xavier") == 0)
		return (TRUE);
	else
		return (FALSE);
}

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

/*int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	**args;

	args = cmd->cmds;
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (get_cd(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (get_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (get_pwd(args));
	// if (ft_strcmp(args[0], "env") == 0)
	// 	return (get_env(shell->env, args[0]));
	// if (ft_strcmp(args[0], "export") == 0)
	// 	return (get_export());
	if (ft_strcmp(args[0], "unset") == 0)
		return (get_unset(shell, args));
	if (ft_strcmp(args[0], "exit") == 0)
		return (get_exit(args));
	return (1);
}*/

/*Exec builtin in the parent process*/

int	exec_builtin_parent(t_cmd *cmd, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;

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
		shell->exit_code = 1;
		return (1);
	}
	shell->exit_code = launch_built(shell, cmd->cmds);
	reset_stdio(stdin_backup, stdout_backup);
	return (0);
}
