/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:11:35 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/20 11:29:00 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Sort an array of environment variables (t_env) alphabetically by key.*/

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

/*Return a newly allocated trimmed copy of the input string,
removing leading and trailing whitespace.*/

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

/*Validate whether a string is a valid export key for environment variables.*/

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

/*Print an error message for a command not found and return exit code 127.*/

int	print_cmd_not_found(t_shell *shell, char *cmd)
{
	if (!cmd || !*cmd)
		ft_printf("Command not found and can't be installed\n");
	else
		ft_printf("%s: command not found\n", cmd);
	shell->exit_code = 127;
	return (127);
}
