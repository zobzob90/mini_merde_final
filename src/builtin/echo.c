/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:49:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/09 14:09:17 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_va(const char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	echo_args(char **av, t_env *env, int start)
{
	int		i;
	char	*val;

	i = start;
	while (av[i])
	{
		if (av[i][0] == '$')
		{
			val = get_env_va(av[i] + 1, env);
			if (val)
				ft_printf("%s", val);
		}
		else
			ft_printf("%s", av[i]);
		if (av[i + 1])
			ft_printf(" ");
		i++;
	}
}

int	get_echo(char **av, t_env *env)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (av[i] && av[i][0] == '-'
			&& ft_strspn(av[i] + 1, "n") == ft_strlen(av[i]) - 1)
	{
		n_flag = 0;
		i++;
	}
	echo_args(av, env, i);
	if (n_flag)
		ft_printf("\n");
	return (0);
}
