/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:53:08 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/24 12:41:58 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_not_found(t_shell *shell, char *cmd)
{
	print_cmd_not_found(shell, cmd);
	shell->exit_code = 127;
	exit_clean_shell(shell, NULL);
	exit(127);
}

static void	handle_not_a_directory(t_shell *shell, char *path)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Not a directory\n", 2);
	shell->exit_code = 126;
	exit_clean_shell(shell, NULL);
	exit(126);
}

static void	handle_is_directory(t_shell *shell, char *path)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	shell->exit_code = 126;
	exit_clean_shell(shell, NULL);
	exit(126);
}

int	check_exec_errors(char *path, t_cmd *cmd, t_shell *shell)
{
	struct stat	sb;

	if (!path || *path == '\0')
		handle_cmd_not_found(shell, cmd->cmds[0]);
	if (stat(path, &sb) == -1)
	{
		if (errno == ENOTDIR)
			handle_not_a_directory(shell, path);
	}
	else if (S_ISDIR(sb.st_mode))
		handle_is_directory(shell, path);
	return (0);
}
