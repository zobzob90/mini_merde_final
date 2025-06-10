/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:00 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_syntax_error(t_shell *shell, const char *msg)
{
	ft_putstr_fd("Error : Unexpected token `", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("`\n", 2);
	shell->exit_code = 258;
	return ;
}

void	parse_tokens(t_shell *shell, t_lexer *lexer, t_cmd *cmd)
{
	while (lexer)
	{
		if (lexer->type == WORD && lexer->value)
			append_cmd(shell, cmd, lexer->value);
		else if (lexer->type == PIPE)
		{
			if (!cmd->cmds || !cmd->cmds[0])
			{
				parser_syntax_error(shell, "|");
				return ;
			}
			cmd = append_pipe(shell, cmd);
		}
		else if (lexer->type == REDIR_IN || lexer->type == REDIR_OUT
			|| lexer->type == APPEND || lexer->type == HEREDOC)
		{
			handle_redir(shell, cmd, lexer);
			if (shell->exit_code == 258)
				return ;
			lexer = lexer->next;
		}
		else
			parser_syntax_error(shell, lexer->value);
		lexer = lexer->next;
	}
}

void	clean_all_quotes(t_lexer *lexer)
{
	while (lexer)
	{
		printf ("[DEBUG W/ QUOTES] lexer->values = %s \n", lexer->value);
		lexer->value = remove_quotes_from_tok(lexer->value);
		printf ("[DEBUG W/O QUOTES] lexer->values = %s \n", lexer->value);
		lexer = lexer->next;
	}
}
void	parser(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
	{
		ft_putstr_fd("Error: Malloc failed in parser\n", 2);
		shell->exit_code = 1;
		return ;
	}
	shell->cmd = cmd;
	//clean_all_quotes(shell->lexer);
	parse_tokens(shell, shell->lexer, cmd);
}
