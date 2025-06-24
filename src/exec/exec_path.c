/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:26:33 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/24 17:01:24 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Count the number of environment variable nodes in the linked list.*/

int	env_list_size(t_env *env)
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

/*Concatenate path and command into a full path, adding '/' if needed.*/

char	*ft_strjoin_path(char *path, char *cmd)
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

/*Find the full executable path of cmd by searching directories in PATH.*/

char	*resolve_cmd_path(char *cmd, t_env *env)
{
	struct stat	sb;
	char		**paths;
	char		*full;
	char		*path_var;
	int			i;

	path_var = get_env_value(env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin_path(paths[i], cmd);
		if (!full)
			return (ft_free_tab(paths), NULL);
		if (access(full, X_OK) == 0 && stat(full, &sb) == 0
			&&S_ISREG(sb.st_mode))
			return (ft_free_tab(paths), full);
		(free(full), i++);
	}
	ft_free_tab(paths);
	return (NULL);
}
