/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:49:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/06 13:45:25 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_va(const char *name, t_env *env)
{
	t_env *tmp = env;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
			return tmp->value;
		tmp = tmp->next;
	}
	return NULL;
}

int	get_echo(char **av, t_env *env)
{
	int	i = 1;
	int	n_flag = 1;
	char *debug = get_env_va("TEST", env);
	if (debug)
    	ft_printf("[DEBUG: TEST=%s]\n", debug);
	else
    	ft_printf("[DEBUG: TEST non trouvé]\n");
	if (av[1] && ft_strcmp(av[1], "-n") == 0)
	{
		n_flag = 0;
		i++;
	}
	while (av[i])
	{
		if (av[i][0] == '$')
		{
			char *val = get_env_va(av[i] + 1, env); // passe env ici
			if (val)
				ft_printf("%s", val);
		}
		else
			ft_printf("%s", av[i]);

		if (av[i + 1])
			ft_printf(" ");
		i++;
	}
	if (n_flag)
		ft_printf("\n");
	return (0);
}
