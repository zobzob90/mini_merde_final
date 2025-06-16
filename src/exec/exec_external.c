/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:41:31 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/16 17:53:59 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_executable_path(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (ft_strchr(cmd->cmds[0], '/'))
		path = ft_strdup(cmd->cmds[0]);
	else
		path = resolve_cmd_path(cmd->cmds[0], env);
	return (path);
}

char	**prepare_envp(t_env *env, char *path)
{
	char	**envp;

	envp = env_list_to_array(env);
	if (!envp)
	{
		free(path);
		return (NULL);
	}
	return (envp);
}

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
		return (S_ISDIR(st.st_mode));
	return (0);
}

void	handle_execve_fail(char *path, char **envp, char *cmd, t_shell *shell)
{
	int	err;

	err = errno;
	perror(cmd);
	free(path);
	ft_free_tab(envp);
	exit_clean_shell(shell, NULL);
	if (err == EACCES || (path && is_directory(path)))
		exit(126);
	else if (err == ENOENT || err == EFAULT)
		exit(127);
	else
		exit(1);
}

void	exec_external(t_cmd *cmd, t_shell *shell)
{
	char		*path;
	char		**envp;
	struct stat	sb;

	if (!cmd || !cmd->cmds || !cmd->cmds[0])
		exit (1);
	path = get_executable_path(cmd, shell->env);
	if (!path || *path == '\0')
	{
		print_cmd_not_found(cmd->cmds[0]);
		exit_clean_shell(shell, NULL);
		exit (127);
	}
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_printf("%s: Is a directory\n", path);
		(free(path), g_last_exit_code = 126,
			exit_clean_shell(shell, NULL), exit(126));
	}
	envp = prepare_envp(shell->env, path);
	if (!envp)
		(free(path), g_last_exit_code = 1, exit(1));
	execve(path, cmd->cmds, envp);
	handle_execve_fail(path, envp, cmd->cmds[0], shell);
}
