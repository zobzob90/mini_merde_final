/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:08:19 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/25 18:04:05 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Convert linked list of environment variables into a
NULL-terminated array of "key=value" strings.*/

char	**env_list_to_array(t_env *env)
{
	char	**envp;
	char	*joined;
	int		size;
	int		i;

	size = env_list_size(env);
	envp = ft_calloc((size + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		joined = ft_strjoin(env->key, "=");
		if (!joined)
			return (ft_free_tab(envp), NULL);
		envp[i] = ft_strjoin(joined, env->value);
		if (!envp[i])
			return (free(joined), ft_free_tab(envp), NULL);
		free(joined);
		i++;
		env = env->next;
	}
	return (envp);
}

int	exec_redir_only(t_cmd *cmd, t_shell *shell, int prev_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		exec_child(cmd, shell, prev_fd, shell->pipe_fd);
	waitpid(pid, &status, 0);
	update_exit_code(shell, status);
	return (0);
}

static void	cleanup_pipe(t_shell *shell, pid_t pid, int *last_pid, int *status)
{
    (void)pid;
    (void)last_pid;
    update_exit_code(shell, *status);
    set_signal_handlers();
    if (shell->pipe_fd[0] >= 0)
        close(shell->pipe_fd[0]);
    if (shell->pipe_fd[1] >= 0)
        close(shell->pipe_fd[1]);
}

int	exec_external_cmd(t_cmd *cmd, t_shell *shell, int *prev_fd, pid_t *last_pid)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (has_next_non_empty_cmd(cmd) && pipe(shell->pipe_fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		(exec_child(cmd, shell, *prev_fd, shell->pipe_fd), exit(EXIT_FAILURE));
	}
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	*last_pid = pid;
	if (!has_next_non_empty_cmd(cmd))
		cleanup_pipe(shell, pid, last_pid, &status);
	else
		handle_parent(pid, cmd, shell->pipe_fd, prev_fd);
	return (0);
}
