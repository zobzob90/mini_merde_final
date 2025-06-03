/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:49:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/02 12:58:15 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo(char **av)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	if (av[1] && ft_strcmp(av[i], "-n") == 0)
	{
		n_flag = 0;
		i++;
	}
	while (av[i])
	{
		ft_printf("%s", av[i]);
		if (av[i + 1])
			ft_printf(" ");
		i++;
	}
	if (n_flag)
		ft_printf("\n");
	return (0);
}
