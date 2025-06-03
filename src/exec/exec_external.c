/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:41:31 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/03 13:46:35 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return the size of the chained link of env variable*/

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*Join path with the cmd name*/

static char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*res;
	int		path_len;
	int		cmd_len;
	int		add_slash;
	int		len;

	res = NULL;
	if (!path || !cmd)
		return (NULL);
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	add_slash = 0;
	if (path_len > 0 && path[path_len - 1] != '/')
		add_slash = 1;
	len = path_len + cmd_len + add_slash + 1;
	res = ft_calloc(len, sizeof(char));
	if (!res)
		return (NULL);
	ft_strcpy(res, path);
	if (add_slash)
		ft_strcat(res, "/");
	ft_strcat(res, cmd);
	return (res);
}

static char	*resolve_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*full;
	char	*path_var;
	int		i;

	i = 0;
	full = NULL;
	path_var = get_env_value(env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full = ft_strjoin_path(paths[i], cmd);
		if (access(full, X_OK) == 0)
			return (ft_free_tab(paths), full);
		if (full)
			free (full);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

static char	**env_list_to_array(t_env *env)
{
	char	**envp;
	char	*joined;
	int		size;
	int		i;

	size = env_list_size(env);
	envp = ft_calloc((size + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		joined = ft_strjoin(env->key, "=");
		if (!joined)
			return (ft_free_tab(envp), NULL);
		envp[i] = ft_strjoin(joined, env->value);
		if (!envp[i])
			return (free(joined), ft_free_tab(envp), NULL);
		free(joined);
		i++;
		env = env->next;
	}
	return (envp);
}

int	exec_external(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	path = NULL;
	if (!cmd || !cmd->cmds || !cmd->cmds[0])
		return (1);
	if (ft_strchr(cmd->cmds[0], '/'))
		path = ft_strdup(cmd->cmds[0]);
	else
		path = resolve_cmd_path(cmd->cmds[0], env);
	if (!path)
		return (perror(cmd->cmds[0]), 127);
	envp = env_list_to_array(env);
	if (!envp)
	{
		free(path);
		return (1);
	}
	execve(path, cmd->cmds, envp);
	perror(cmd->cmds[0]);
	ft_free_tab(envp);
	free(path);
	exit(126);
}
