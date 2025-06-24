/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:47:34 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/24 12:34:21 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates a new environment variable node from a "key=value"
string or returns NULL on failure.*/

t_env	*new_node(char *env_str)
{
	t_env	*new_node;
	char	*equal_pos;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_pos = ft_strchr(env_str, '=');
	if (!equal_pos)
		return (free(new_node), NULL);
	new_node->key = ft_strndup(env_str, equal_pos - env_str);
	if (!new_node->key)
		return (free(new_node), NULL);
	new_node->value = ft_strdup(equal_pos + 1);
	if (!new_node->value)
		return (free(new_node->key), free(new_node), NULL);
	if (!*new_node->key)
		return (free(new_node->value), free(new_node->key),
			free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

/*Adds a new environment variable node if the key
does not already exist in the list.*/

static void	add_env_if_missing(t_env **env, const char *key, const char *value)
{
	t_env	*new;
	t_env	*last;

	if (get_env_value(*env, key) == NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->next = NULL;
		if (!*env)
			*env = new;
		else
		{
			last = *env;
			while (last->next)
				last = last->next;
			last->next = new;
		}	
	}
}

/*Initializes the shell environment list from the provided envp array,
adding a default TERM if missing.*/

void	init_env(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*last;
	int		i;

	i = 0;
	if (!envp || !*envp)
		return ;
	while (envp[i])
	{
		new = new_node(envp[i]);
		if (!new)
			exit_clean_shell(shell, "Error\n");
		if (!shell->env)
			shell->env = new;
		else
		{
			last = shell->env;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		i++;
	}
	add_env_if_missing(&shell->env, "TERM", "xterm-256color");
}

/*Prints all environment variables in the format "key=value".*/

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		else
			printf("%s=\n", env->key);
		env = env->next;
	}
}
