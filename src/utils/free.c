/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:13:17 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/16 17:44:56 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	if (shell->lexer)
		free_lexer(shell->lexer);
	if (shell->cmd)
		free_pars(shell->cmd);
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		free(temp->file);
		free(temp);
	}
}

void	free_pars(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		if (temp->cmds)
			ft_free_tab(temp->cmds);
		if (temp->cmd_path)
			free(temp->cmd_path);
		if (temp->redir)
			free_redir(temp->redir);
		free(temp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
