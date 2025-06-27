/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/27 09:01:08 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handle WORD tokens by appending them to the current command.*/

static void	handle_word_token(t_shell *shell, t_cmd *cmd, t_lexer *lexer)
{
	if (lexer->type == WORD && lexer->value)
		append_cmd(shell, cmd, lexer->value);
}

/*Handle PIPE tokens with syntax validation.*/

static t_cmd	*handle_pipe_token(t_shell *shell, t_cmd *cmd, t_lexer *lexer)
{
	if ((!cmd->cmds || !cmd->cmds[0]) && !cmd->redir)
	{
		parser_syntax_error(shell, "|");
		return (cmd);
	}
	if (!lexer->next || lexer->next->type == PIPE)
	{
		parser_syntax_error(shell, "|");
		return (cmd);
	}
	return (append_pipe(shell, cmd));
}

/*Handle redirection tokens and advance lexer position.*/

static void	handle_redir_token(t_shell *shell, t_cmd *cmd, t_lexer **lexer)
{
	handle_redir(shell, cmd, *lexer);
	if (shell->exit_code == 2)
		return ;
	*lexer = (*lexer)->next;
}

/*Parse the lexer tokens and build the command structure,
handling pipes and redirections.*/

void	parse_tokens(t_shell *shell, t_lexer *lexer, t_cmd *cmd)
{
	while (lexer)
	{
		if (lexer->type == WORD && lexer->value)
			handle_word_token(shell, cmd, lexer);
		else if (lexer->type == PIPE)
		{
			cmd = handle_pipe_token(shell, cmd, lexer);
			if (shell->exit_code == 2)
				return ;
		}
		else if (lexer->type == REDIR_IN || lexer->type == REDIR_OUT
			|| lexer->type == APPEND || lexer->type == HEREDOC)
		{
			handle_redir_token(shell, cmd, &lexer);
			if (shell->exit_code == 2)
				return ;
		}
		else
			parser_syntax_error(shell, lexer->value);
		lexer = lexer->next;
	}
}

/*Entry point for the parser: initializes command structures,
expands tokens, and parses the lexer.*/

void	parser(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
	{
		ft_putstr_fd("Error: Malloc failed in parser\n", 2);
		g_signal = 1;
		return ;
	}
	if (!check_redir_syntax(shell, shell->lexer))
		return ;
	shell->cmd = cmd;
	expand_all_tokens(shell->lexer, shell);
	parse_tokens(shell, shell->lexer, cmd);
	if (shell->exit_code == 2)
	{
		free_pars(shell->cmd);
		shell->cmd = NULL;
	}
}
