/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:24:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/05/19 13:15:08 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_pipe(const char c)
{
	if (c == '|')
		return (PIPE);
	return (0);
}

int	is_redir(const char *c, int i)
{
	if (c[i] == '<')
	{
		if (c[i + 1] == '<')
			return (HEREDOC);
		else
			return (REDIR_IN);
	}
	if (c[i] == '>')
	{
		if (c[i + 1] == '>')
			return (APPEND);
		else
			return (REDIR_OUT);
	}
	return (0);
}

int	check_redir_syntax(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type == REDIR_IN || lexer->type == REDIR_OUT
			|| lexer->type == APPEND || lexer->type == HEREDOC)
		{
			if (!lexer->next || lexer->next->type != WORD)
			{
				ft_putstr_fd("Error: Syntax error near unexpected token\n", 2);
				return (0);
			}
		}
		lexer = lexer->next;
	}
	return (1);
}
