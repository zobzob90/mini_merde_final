/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:41:31 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/11 15:02:56 by ertrigna         ###   ########.fr       */
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

void	handle_execve_failure(char *path, char **envp, const char *cmd)
{
	int err;

	err = errno;
	perror(cmd);
	free(path);
	ft_free_tab(envp);
	if (err == EACCES)
		exit(126);
	else if (err == ENOENT)
		exit(127);
	else
		exit(1);
}

int	exec_external(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	if (!cmd || !cmd->cmds || !cmd->cmds[0])
		return (1);
	path = get_executable_path(cmd, env);
	if (!path)
		return (127);
	envp = prepare_envp(env, path);
	if (!envp)
	{
		free(path);
		return (1);
	}
	execve(path, cmd->cmds, envp);
	handle_execve_failure(path, envp, cmd->cmds[0]);
	return (1);
}
