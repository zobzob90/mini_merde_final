/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:35:40 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/20 13:02:57 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates a new environment variable node with the given key and value,
exiting on allocation failure.*/

t_env	*create_env_node(const char *key, const char *value, t_shell *shell)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		exit_clean_shell(shell, "Error: Malloc failed in create_env_node");
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || (value && !new_node->value))
		exit_clean_shell(shell, "Error: Malloc failed in create_env_node");
	return (new_node);
}

/*Adds a new environment variable or updates an existing
one if the key already exists.*/

void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	if (value == NULL)
		return (ft_putstr_fd("export : invalid format\n", 2));
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		exit_clean_shell(NULL, "Error: Malloc failed in add_or_update_env");
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

/*Handles export of a key without a value, validating the key
before adding it to the environment.*/

void	handle_key(t_env **env, char *arg, t_shell *shell)
{
	char	*key;

	key = safe_trim(arg);
	if (!key)
		exit_clean_shell(shell, "malloc failed");
	if (is_valid_export_key(key))
		add_or_update_env(env, key, NULL);
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		shell->exit_code = 1;
	}
	free(key);
}

/*Handles export of a key-value pair by splitting and validating
both components before storing them.*/

void	handle_key_value(t_env **env, char *arg, char *equal, t_shell *shell)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal - arg);
	value = safe_trim(equal + 1);
	if (!key || !value)
		exit_clean_shell(shell, "malloc failed");
	if (is_valid_export_key(key))
		add_or_update_env(env, key, value);
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		shell->exit_code = 1;
	}
	free(key);
	free(value);
}

/*Processes an export argument, optionally joining it with the next
if needed, and adds it to the environment.*/

bool	export_args(t_env **env, char *arg, char *next_arg, t_shell *shell)
{
	char	*equal_sign;
	char	*joined_arg;
	bool	skip_next;

	joined_arg = NULL;
	skip_next = false;
	if (!arg || !*arg)
		return (false);
	if (arg[ft_strlen(arg) - 1] == '=' && next_arg)
	{
		joined_arg = ft_strjoin(arg, next_arg);
		if (!joined_arg)
			exit_clean_shell(shell, "malloc failed");
		arg = joined_arg;
		skip_next = true;
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		handle_key_value(env, arg, equal_sign, shell);
	else
		handle_key(env, arg, shell);
	free(joined_arg);
	return (skip_next);
}
