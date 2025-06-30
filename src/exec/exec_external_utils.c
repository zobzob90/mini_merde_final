/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:53:08 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/30 09:42:59 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Check if the path should be freed (if it was allocated by resolve_cmd_path)*/

int	should_free_path(t_cmd *cmd, char *path)
{
	if (!path)
		return (0);
	if (path != cmd->cmds[0])
		return (1);
	return (0);
}

static void	handle_cmd_not_found(t_shell *shell, char *cmd)
{
	print_cmd_not_found(shell, cmd);
	shell->exit_code = 127;
	exit_clean_shell(shell, NULL);
	exit(127);
}

static void	handle_not_a_directory(t_shell *shell, char *path, t_cmd *cmd)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Not a directory\n", 2);
	shell->exit_code = 126;
	if (should_free_path(cmd, path))
		free(path);
	exit_clean_shell(shell, NULL);
	exit(126);
}

static void	handle_is_directory(t_shell *shell, char *path, t_cmd *cmd)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	shell->exit_code = 126;
	if (should_free_path(cmd, path))
		free(path);
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
			handle_not_a_directory(shell, path, cmd);
	}
	else if (S_ISDIR(sb.st_mode))
		handle_is_directory(shell, path, cmd);
	return (0);
}
