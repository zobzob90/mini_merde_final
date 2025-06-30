/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:30 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/30 08:50:28 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cmd_result(int ret, t_cmd **cmd,
	int *has_real_commands, int *i)
{
	if (ret > 0)
		return (ret);
	if (ret == -1)
		return (-1);
	if (ret == 1)
	{
		*cmd = (*cmd)->next;
		return (0);
	}
	*has_real_commands = 1;
	(*i)++;
	*cmd = (*cmd)->next;
	return (0);
}

static int	finalize_pipeline(int prev_fd, int has_real_commands,
	int i, t_shell *shell)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (!has_real_commands && i == 0)
	{
		shell->exit_code = 0;
		return (0);
	}
	return (i);
}

static int	launch_pipeline(t_shell *shell, t_cmd *cmd, pid_t *pids)
{
	int		prev_fd;
	int		i;
	int		ret;
	int		has_real_commands;

	prev_fd = -1;
	i = 0;
	has_real_commands = 0;
	while (cmd)
	{
		pids[i] = 0;
		ret = process_cmd_node(cmd, shell, &prev_fd, &(pids[i]));
		ret = handle_cmd_result(ret, &cmd, &has_real_commands, &i);
		if (ret != 0)
			return (ret);
		if (ret == 0 && cmd == NULL)
			break ;
	}
	return (finalize_pipeline(prev_fd, has_real_commands, i, shell));
}

/*Main fonction of the exec.*/

int	exec_cmds(t_shell *shell, t_cmd *cmd)
{
	pid_t	pids[MAX_PIPE];
	int		j;
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (setup_heredocs(cmd, shell) != 0)
		return (heredoc_fail(shell));
	i = launch_pipeline(shell, cmd, pids);
	if (i < 0)
		return (-1);
	if (i == 0 || (i == 1 && pids[0] == 0))
		return (shell->exit_code);
	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		j++;
	}
	update_exit_code(shell, status);
	cleanup_heredocs(shell->cmd);
	return (shell->exit_code);
}
