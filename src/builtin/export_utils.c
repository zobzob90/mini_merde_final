/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:35:40 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/06 13:25:29 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(const char *key, const char *value, t_shell *shell)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		exit_clean_shell(shell, "Error: Malloc failed in create_env_node");
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || (value && !new_node->value))
		exit_clean_shell(shell, "Error: Malloc failed in strdup create_env_node");
	return (new_node);
}

void add_or_update_env(t_env **env, char *key, char *value)
{
    t_env *tmp = *env;
    while (tmp)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = value ? strdup(value) : NULL;
            return;
        }
        tmp = tmp->next;
    }
    // Ajout si la clé n'existait pas
    t_env *new = malloc(sizeof(t_env));
    new->key = strdup(key);
    new->value = value ? strdup(value) : NULL;
    new->next = *env;
    *env = new;
}

int	is_valid_export_key(const char *key)
{
	int	i;

	i = 0;
	if (!key || !key[0] ||(!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*safe_trim(const char *str)
{
	char	*start = (char *)str;
	char	*end;
	char	*trimmed;
	size_t	len;

	while (*start && ft_isspace(*start))
		start++;
	end = start + ft_strlen(start);
	while (end > start && ft_isspace(*(end - 1)))
		end--;
	len = end - start;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, start, len + 1);
	return (trimmed);
}

void	handle_key(t_env **env, char *arg, t_shell *shell)
{
	char *key = safe_trim(arg);

	if (!key)
		exit_clean_shell(shell, "malloc failed");

	if (is_valid_export_key(key))
		add_or_update_env(env, key, NULL);
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	free(key);
}

void	handle_key_value(t_env **env, char *arg, char *equal_pos, t_shell *shell)
{
	char *key = ft_substr(arg, 0, equal_pos - arg);
	char *value = safe_trim(equal_pos + 1);

	if (!key || !value)
		exit_clean_shell(shell, "malloc failed");

	if (is_valid_export_key(key))
		add_or_update_env(env, key, value);
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	free(key);
	free(value);
}

bool	export_args(t_env **env, char *arg, char *next_arg, t_shell *shell)
{
	char	*equal_sign;
	char	*joined_arg = NULL;
	bool	skip_next = false;

	if (!arg || !*arg)
		return false;
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
	return skip_next;
}
