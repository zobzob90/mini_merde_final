/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:51:41 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/23 18:28:24 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handle incoming signals (e.g., SIGINT, SIGQUIT)
and update readline and global exit code.*/

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		(void)signal;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		g_signal = SIGQUIT;
		return ;
	}
}

/*Set up the signal handlers for SIGINT and SIGQUIT used in the shell.*/

void	set_signal_handlers(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	exit_sigint(t_shell *shell)
{
	if (g_signal == SIGINT)
		shell->tmp_exit_code = 130;
	if (g_signal == SIGQUIT)
		shell->tmp_exit_code = 131;
	g_signal = 0;
	return ;
}
