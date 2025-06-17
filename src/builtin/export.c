/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:44:28 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/09 13:35:44 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Converts the linked list of environment variables
into an array for easier processing and sorting.*/

static t_env	**env_to_array(t_env *env, int *size)
{
	t_env	*tmp;
	t_env	**array;
	int		count;
	int		i;

	tmp = env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	*size = count;
	array = malloc(sizeof(t_env *) * count);
	if (!array)
		return (NULL);
	tmp = env;
	i = 0;
	while (i < count)
	{
		array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	return (array);
}

/*Prints all environment variables in a sorted, export-compatible format.*/

static int	print_export(t_env *env)
{
	t_env	**array;
	int		size;
	int		i;

	i = 0;
	array = env_to_array(env, &size);
	if (!array)
		return (1);
	ft_sort_str_array(array, size);
	while (i < size)
	{
		ft_printf("declare -x %s", array[i]->key);
		if (array[i]->value)
			ft_printf("=\"%s\"", array[i]->value);
		ft_printf("\n");
		i++;
	}
	free(array);
	return (0);
}

/*Implements the built-in 'export' command, either printing
or updating environment variables.*/

int	get_export(t_shell *shell, char **argv)
{
	int		i;
	bool	skip_next;

	i = 1;
	if (!argv[1])
		return (print_export(shell->env));
	while (argv[i])
	{
		skip_next = export_args(&shell->env, argv[i], argv[i + 1], shell);
		if (skip_next)
			i++;
		i++;
	}
	return (0);
}
