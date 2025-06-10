/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:57:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/10 15:26:26 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(char **av)
{
	char	cwd[PATH_MAX];

	(void)av;
	if (av[0][1])
	{
		ft_putstr_fd("bash: pwd: invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd [-L-P]\n", 2);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	perror("getcwd() error");
	return (1);
}
