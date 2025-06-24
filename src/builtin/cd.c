/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:57:05 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/24 12:38:21 by ertrigna         ###   ########.fr       */
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

static void	update_env_var(t_env *env, const char *key, const char *value)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(value);
			return ;
		}
		cur = cur->next;
	}
}

/*Updates the PWD and OLDPWD environment variables after
changing the working directory.*/

static void	update_pwd_env(t_shell *shell, const char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_env_var(shell->env, "PWD", cwd);
		if (oldpwd)
			update_env_var(shell->env, "OLDPWD", oldpwd);
	}
}

/*Implements the built-in 'cd' command: changes the current
directory and manages related environment variables.*/

int	get_cd(t_shell *shell, char **av)
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
	update_pwd_env(shell, oldpwd);
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
