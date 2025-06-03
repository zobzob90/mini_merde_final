/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:57:11 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/03 15:01:37 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit(char **av)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	ft_printf("exit\n");
	if (av[1])
	{
		if (av[1][0] == '-' || av[1][0] == '+')
			i++;
		while (av[1][i])
		{
			if (!ft_isdigit(av[1][i]))
				(ft_printf("exit: %s: numeric argument required\n", av[1]),
					exit(2));
			i++;
		}
		if (av[2])
		{
			ft_printf("minishell : exit: too many arguments\n");
			return (1);
		}
		status = ft_atoi(av[1]);
	}
	exit(status);
}
