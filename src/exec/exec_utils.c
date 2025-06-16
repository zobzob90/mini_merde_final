/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:08:19 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/16 17:47:43 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Transform the struct env in a **char*/

char	**env_list_to_array(t_env *env)
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
