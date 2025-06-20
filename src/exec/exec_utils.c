/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:08:19 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/20 17:12:16 by ertrigna         ###   ########.fr       */
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

int	exec_external_cmd(t_cmd *cmd, t_shell *shell, int *prev_fd, pid_t *last_pid)
{
	pid_t	pid;

	if (cmd->next && pipe(shell->pipe_fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		exec_child(cmd, shell, *prev_fd, shell->pipe_fd);
	*last_pid = handle_parent(pid, cmd, shell->pipe_fd, prev_fd);
	return (0);
}

int	try_exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (is_builtin(cmd->cmds[0]) && !cmd->next && !cmd->prev)
		return (exec_builtin_parent(cmd, shell));
	return (-1);
}

int	skip_empty_node(t_cmd **cmd)
{
	if ((!(*cmd)->cmds || !(*cmd)->cmds[0]) && !(*cmd)->redir)
	{
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}
