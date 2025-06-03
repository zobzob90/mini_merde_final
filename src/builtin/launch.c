/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:01:19 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/03 13:53:39 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_built(t_shell *shell)
{
	print_env(shell->env);
	return (0);
}

static int	launch_easter(t_shell *shell, char **argv)
{
	if (ft_strcmp(argv[0], "michel") == 0)
		return (get_drucker(shell));
	else if (ft_strcmp(argv[0], "jacquie") == 0)
		return (get_jacquie(shell));
	else if (ft_strcmp(argv[0], "hell") == 0)
		return (get_hell(shell));
	else if (ft_strcmp(argv[0], "res") == 0)
		return (get_reset(shell));
	else if (ft_strcmp(argv[0], "merde") == 0)
		return (get_shit(shell));
	else if (ft_strcmp(argv[0], "drucker") == 0)
	{
		if (shell->drucker_mode)
			return (get_drucker(shell));
		else
			ft_putstr_fd("Tu n'es pas le vrai Drucker, imposteur ! 🚨\n", 2);
		return (-1);
	}
	else if (ft_strcmp(argv[0], "reset") == 0)
		return (get_reset(shell));
	else if (ft_strcmp(argv[0], "sudo") == 0)
		ft_putstr_fd("Tu n'es pas le vrai bash, imposteur ! 🚨\n", 2);
	return (-1);
}

int	launch_built(t_shell *shell, char **argv)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (get_cd(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (get_pwd(argv));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (get_echo(argv));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (get_exit(argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (get_env_built(shell));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (get_unset(shell, argv));
	// else if (ft_strcmp(argv[0], "export") == 0)
	//  	return (get_export(shell, (t_cmd *)argv));
	else
	{
		if (launch_easter(shell, argv) != -1)
			return (0);
	}
	return (-1);
}
