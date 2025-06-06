/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:44:28 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/06 14:00:15 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}*/

/*static char **env_keys_array(t_env *env)
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
		arr[i++] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}	
	arr[i] = NULL;
	return (arr);
}*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

static t_env	**env_to_array(t_env *env, int *size)
{
	t_env *tmp = env;
	int count = 0;
	while (tmp) { count++; tmp = tmp->next; }

	*size = count;
	t_env **array = malloc(sizeof(t_env *) * count);
	if (!array)
		return (NULL);

	tmp = env;
	for (int i = 0; i < count; i++)
	{
		array[i] = tmp;
		tmp = tmp->next;
	}
	return array;
}

static int compare_env(const void *a, const void *b)
{
	t_env *ea = *(t_env **)a;
	t_env *eb = *(t_env **)b;
	return ft_strcmp(ea->key, eb->key);
}

static int	print_export(t_env *env)
{
	int size = 0;
	t_env **array = env_to_array(env, &size);
	if (!array)
		return (1);

	qsort(array, size, sizeof(t_env *), compare_env);
	for (int i = 0; i < size; i++)
	{
		printf("declare -x %s", array[i]->key);
		if (array[i]->value)
			printf("=\"%s\"", array[i]->value);
		printf("\n");
	}
	free(array);
	return (0);
}

int	get_export(t_shell *shell, char **argv)
{
	int		i;
	bool	skip_next;

	i = 1;
	if (!argv[1])
		return print_export(shell->env);
	while (argv[i])
	{
		skip_next = export_args(&shell->env, argv[i], argv[i + 1], shell);
		if (skip_next)
			i++;
		i++;
	}
	return 0;
}
