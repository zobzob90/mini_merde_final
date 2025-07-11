/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:49:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/30 15:41:20 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Prints the arguments starting from a given index, separated by spaces.*/

static void	echo_args(char **av, int start)
{
	int		i;

	i = start;
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
}

/*Implements the built-in 'echo' command, handling the optional
'-n' flag to suppress the trailing newline.*/

int	get_echo(char **av)
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
	echo_args(av, i);
	if (n_flag)
		printf("\n");
	return (0);
}
