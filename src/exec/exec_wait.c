/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:51:42 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/16 16:48:22 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Wait the end of all children.*/

void	wait_all_children(pid_t last_pid, int *status)
{
	pid_t	pid;
	int		wstatus;

	pid = wait(&wstatus);
	while (pid > 0)
	{
		if (pid == last_pid)
			*status = wstatus;
		pid = wait(&wstatus);
	}
}

/*Wait the end of the process designed by pid and return the status.*/

int	wait_and_return_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
