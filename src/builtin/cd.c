/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:57:05 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/03 13:40:38 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns the appropriate path for the 'cd' command based
on user input or environment variables.*/

static char	*get_cd_path(char **av)
{
	if (av[1] == NULL || av[1][0] == '\0')
		return (getenv("HOME"));
	if (ft_strcmp(av[1], "-") == 0)
		return (getenv("OLDPWD"));
	return (av[1]);
}

/*Prints an error message to stderr and returns 1 to indicate failure.*/

static int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

/*Updates the PWD and OLDPWD environment variables after
changing the working directory.*/

static void	update_pwd_env(const char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
		if (oldpwd)
			setenv("OLDPWD", oldpwd, 1);
	}
}

/*Implements the built-in 'cd' command: changes the current
directory and manages related environment variables.*/

int	get_cd(char **av)
{
	char	oldpwd[PATH_MAX];
	char	cwd[PATH_MAX];
	char	*path;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	path = get_cd_path(av);
	if (!path)
	{
		if (av[1] && ft_strcmp(av[1], "-") == 0)
			return (print_error("Minishell: cd: OLDPWD not set\n"));
		return (print_error("Minishell: cd: HOME not set\n"));
	}
	if (chdir(path) == -1)
		return (perror("Minishell: cd"), 1);
	update_pwd_env(oldpwd);
	if (av[1] && ft_strcmp(av[1], "-") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			ft_putstr_fd(cwd, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}
