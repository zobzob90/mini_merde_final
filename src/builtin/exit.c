/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:57:11 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/20 14:39:43 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if the given string represents a valid
numeric argument (optional sign followed by digits).*/

static int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*Implements the built-in 'exit' command, handling numeric
arguments and cleanup before exiting the shell.*/

int	get_exit(char **av, t_shell *shell)
{
	int	status;

	status = 0;
	ft_printf("exit\n");
	if (av[1])
	{
		if (!is_numeric_arg(av[1]))
		{
			ft_printf("exit: %s: numeric argument required\n", av[1]);
			free_shell(shell);
			exit(2);
		}
		if (av[2])
		{
			ft_printf("minishell : exit: too many arguments\n");\
			free_shell(shell);
			exit(2);
		}
		status = ft_atoi(av[1]);
	}
	close(shell->fd_in);
	close(shell->fd_out);
	free_shell(shell);
	return (status % 256);
}
