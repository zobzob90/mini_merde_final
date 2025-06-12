/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:20:41 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/12 13:46:26 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_add_node(t_shell *shell, t_token type, char *file)
{
	t_redir	*redir;

	redir = new_redir();
	(void)shell;
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		ft_putstr_fd("Error: Malloc failed in redir_add_node\n", 2);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	append_redir(t_redir **redir, t_redir *new)
{
	t_redir	*temp;

	if (!*redir)
	{
		*redir = new;
		return ;
	}
	temp = *redir;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	handle_redir(t_shell *shell, t_cmd *cmd, t_lexer *lex)
{
	t_token	type;
	t_redir	*redir;

	type = lex->type;
	if (!cmd->cmds || !cmd->cmds[0])
	{
		ft_putstr_fd("Error: No command before redirection\n", 2);
		g_last_exit_code = 2;
		return ;
	}
	if (!lex || !lex->next || lex->next->type != WORD)
	{
		ft_putstr_fd("Error: Missing file after redirection\n", 2);
		g_last_exit_code = 2;
		return ;
	}
	redir = redir_add_node(shell, type, lex->next->value);
	append_redir(&cmd->redir, redir);
}

void	append_cmd(t_shell *shell, t_cmd *cmd, char *input)
{
	int		i;
	char	**temp;

	i = 0;
	while (cmd->cmds && cmd->cmds[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		exit_clean_shell(shell, "Malloc Error in append_cmd\n");
	i = 0;
	while (cmd->cmds && cmd->cmds[i])
	{
		temp[i] = ft_strdup(cmd->cmds[i]);
		i++;
	}
	if (input)
	{
		temp[i] = ft_strdup(input);
		i++;
	}
	temp[i] = NULL;
	if (cmd->cmds)
		ft_free_tab(cmd->cmds);
	cmd->cmds = temp;
}

t_cmd	*append_pipe(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*new;

	new = new_cmd();
	if (!new)
		exit_clean_shell(shell, "Malloc Error in append_pipe\n");
	cmd->next = new;
	new->prev = cmd;
	return (new);
}
