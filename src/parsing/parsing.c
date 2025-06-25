/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/25 17:36:58 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Print a syntax error message and set the shell's exit codes.*/

void	parser_syntax_error(t_shell *shell, const char *msg)
{
	ft_putstr_fd("Error : Unexpected token `", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("`\n", 2);
	shell->exit_code = 2;
	return ;
}

/*Parse the lexer tokens and build the command structure,
handling pipes and redirections.*/

void	parse_tokens(t_shell *shell, t_lexer *lexer, t_cmd *cmd)
{
	while (lexer)
	{
		if (lexer->type == WORD && lexer->value)
			append_cmd(shell, cmd, lexer->value);
		else if (lexer->type == PIPE)
		{
			if ((!cmd->cmds || !cmd->cmds[0])
				|| !lexer->next || lexer->next->type == PIPE)
				return (parser_syntax_error(shell, "|"));
			cmd = append_pipe(shell, cmd);
		}
		else if (lexer->type == REDIR_IN || lexer->type == REDIR_OUT
			|| lexer->type == APPEND || lexer->type == HEREDOC)
		{
			handle_redir(shell, cmd, lexer);
			if (shell->exit_code == 2)
				return ;
			lexer = lexer->next;
		}
		else
			parser_syntax_error(shell, lexer->value);
		lexer = lexer->next;
	}
}

/*Remove surrounding quotes from each token in the lexer list.*/

void	clean_all_quotes(t_lexer *lexer)
{
	while (lexer)
	{
		lexer->value = remove_quotes_from_tok(lexer->value);
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
