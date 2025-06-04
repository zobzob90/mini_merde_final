/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:44:28 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/04 14:39:30 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count(t_env *env)
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

static char **env_keys_array(t_env *env)
{
	int		i;
	int		count;
	char	**arr;
	t_env	*tmp;

	i = 0;
	count = env_count(env);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		arr[i++] = tmp->key;
		tmp = tmp->next;
	}	
	arr[i] = NULL;
	return (arr);
}

static void	print_exported_env(t_env *env)
{
	char	**keys;
	int		i;
	char	*value;

	keys = env_keys_array(env);
	if (!keys)
		return;
	ft_sort_str_array(keys);
	i = 0;
	while (keys[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(keys[i], STDOUT_FILENO);
		value = get_env_value(env, keys[i]);
		if (value != NULL)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free(keys);
}

int	get_export(t_shell *shell, t_cmd *cmd)
{
	int		i;
	bool	skip_next;

	i = 1;
	if (!cmd->cmds[1])
	{
		print_exported_env(shell->env);
		return (0);
	}
	while (cmd->cmds[i])
	{
		skip_next = export_args(&shell->env, cmd->cmds[i], cmd->cmds[i + 1], shell);
		if (skip_next)
			i++;
		i++;
	}
	return (0);
}
