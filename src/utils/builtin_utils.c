/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:11:35 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/12 14:48:14 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sort_str_array(t_env	**arr, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*safe_trim(const char *str)
{
	char	*start;
	char	*end;
	char	*trimmed;
	size_t	len;

	start = (char *)str;
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

int	is_valid_export_key(const char *key)
{
	int	i;

	i = 0;
	if (!key || !key[0] || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_cmd_not_found(char *cmd)
{
	ft_printf("%s: command not found\n", cmd);
	g_last_exit_code = 127;
	return (127);
}
