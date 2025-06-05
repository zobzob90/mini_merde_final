/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:57:09 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/05 14:59:31 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_drucker(t_shell *shell)
{
	if (!shell->drucker_mode)
	{
		shell->drucker_mode = 1;
		ft_putstr_fd("Mode Michel Drucker activé 🎙️\n", 1);
	}
	return (0);
}

int	get_jacquie(t_shell *shell)
{
	if (!shell->drucker_mode)
	{
		shell->drucker_mode = 2;
		ft_putstr_fd("Mode Jacquie activé 🍆💧💋\n", 1);
	}
	return (0);
}

int	get_hell(t_shell *shell)
{
	if (!shell->drucker_mode)
	{
		shell->drucker_mode = 3;
		ft_putstr_fd("Mode Hell activé 🔥\n", 1);
	}
	return (0);
}

int	get_reset(t_shell *shell)
{
	if (shell->drucker_mode)
	{
		shell->drucker_mode = 0;
		ft_putstr_fd("Mode désactivé ❌\n", 1);
	}
	return (0);
}

int	get_shit(t_shell *shell)
{
	if (!shell->drucker_mode)
	{
		shell->drucker_mode = 4;
		ft_putstr_fd("Hum tu as fait un gros caca 💩\n", 1);
	}
	return (0);
}
