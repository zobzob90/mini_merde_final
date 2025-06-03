/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:35:40 by ertrigna          #+#    #+#             */
/*   Updated: 2025/05/27 15:09:46 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_env *create_env_node(const char *key, const char *value, t_shell *shell)
{
	t_env *new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		exit_clean_shell(shell, "Error: Malloc failed in create_env_node");
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
		exit_clean_shell(shell, "Error: Malloc failed in strdup create_env_node");
	return (new_node);
}

void add_or_update_env(t_env **env, const char *key, const char *value, t_shell *shell)
{
	t_env *temp;
	t_env *new_node;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				exit_clean_shell(shell, "Error: Malloc failed in add_or_update_env");
			return;
		}
		temp = temp->next;
	}
	new_node = create_env_node(key, value, shell);
	new_node->next = *env;
	if (*env)
		(*env)->prev = new_node;
	*env = new_node;
	shell->env = *env;
}

int	is_valid_export_key(const char *key)
{
	int i;

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

void	trim_space(char *av)
{
	char *start;
	char *end;

	start = av;
	while (*start && ft_isspace(start))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_isspace(end))
		end--;
	*(end + 1) = '\0';
	if (start != av)
	{
		while (*start)
		{
			*av++ = *start++;
		}
		*av = '\0';
	}
}

void handle_key(t_env *env, char *av, char *equal, t_shell *shell)
{
	trim_space(av);
	if(is_valid_export_key(av))
		add_or_update_env(&env, av, "", shell);
	else
		ft_putstr_fd("minishell: export: not a valid identifier`", 2);
}

void handle_key_value(t_env *env, char *av, char *next_equal, t_shell *shell)
{
	trim_space(av);
	trim_space(next_equal + 1);
	if (is_valid_export_key(av))
		add_or_update_env(&env, av, next_equal + 1, shell);
	else
		ft_putstr_fd("minishell: export: not a valid identifier`", 2);
}

bool	export_args(t_env *env, char *arg, char *next_arg, t_shell *shell)
{
	char	*equal_sign;
	char	*joined_arg;
	bool	skip_next;

	skip_next = false;
	joined_arg = NULL;
	trim_spaces(arg);
	if (arg && arg[ft_strlen(arg) - 1] == '=' && next_arg)
	{
		joined_arg = ft_strjoin(arg, next_arg);
		if (!joined_arg)
			return (ft_putstr_fd("Error: malloc\n", STDERR_FILENO), false);
		arg = joined_arg;
		skip_next = true;
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		handle_assignment(env, arg, equal_sign, shell);
		*equal_sign = '=';
	}
	else
		is_valid_export_key(env, arg, shell);
	return (free_joined(joined_arg), skip_next);
}


int	get_export(t_shell *shell, t_cmd *cmd)
{
	bool	skip;
	int		i;

	if (!cmd->cmds[1])
		return (-1);
	i = 1;
	while (cmd->cmds[i])
	{
		skip = export_args(shell->env, cmd->cmds[i], cmd->cmds[i + 1],
				shell);
		if (skip)
			i++;
		i++;
	}
	return (0);
}*/
