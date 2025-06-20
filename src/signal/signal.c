/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:51:41 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/20 17:34:18 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handle incoming signals (e.g., SIGINT, SIGQUIT)
and update readline and global exit code.*/

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_last_exit_code = 130;
	}
	else if (signal == SIGQUIT)
	{
		return ;
	}
}

/*Set up the signal handlers for SIGINT and SIGQUIT used in the shell.*/

void	set_signal_handlers(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
