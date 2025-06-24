/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:41:31 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/24 16:54:15 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Get the full executable path for a command.*/

char	*get_executable_path(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (ft_strchr(cmd->cmds[0], '/'))
		path = ft_strdup(cmd->cmds[0]);
	else
		path = resolve_cmd_path(cmd->cmds[0], env);
	return (path);
}

/*Convert environment linked list to envp array.*/

char	**prepare_envp(t_env *env, char *path)
{
	char	**envp;

	envp = env_list_to_array(env);
	if (!envp)
	{
		free(path);
		return (NULL);
	}
	return (envp);
}

/*Check if given path is a directory.*/

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
		return (S_ISDIR(st.st_mode));
	return (0);
}

/*Handle execve failure and exit.*/

void	handle_execve_fail(char *path, char **envp, char *cmd, t_shell *shell)
{
	int	err;

	err = errno;
	perror(cmd);
	free(path);
	ft_free_tab(envp);
	exit_clean_shell(shell, NULL);
	if (err == EACCES || (path && is_directory(path)))
		exit(126);
	else if (err == ENOENT || err == EFAULT)
		exit(127);
	else
		exit(1);
}

/*Execute an external command using execve.*/

void	exec_external(t_cmd *cmd, t_shell *shell)
{
	char		*path;
	char		**envp;

	if (!cmd || !cmd->cmds || !cmd->cmds[0])
		exit (1);
	path = get_executable_path(cmd, shell->env);
	check_exec_errors(path, cmd, shell);
	envp = prepare_envp(shell->env, path);
	if (!envp)
		(free(path), shell->exit_code = 1, exit(1));
	execve(path, cmd->cmds, envp);
	handle_execve_fail(path, envp, cmd->cmds[0], shell);
}
