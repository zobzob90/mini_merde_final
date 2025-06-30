/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 08:51:25 by valentin          #+#    #+#             */
/*   Updated: 2025/06/27 08:55:24 by valentin         ###   ########.fr       */
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

/*Remove surrounding quotes from each token in the lexer list.*/

void	clean_all_quotes(t_lexer *lexer)
{
	while (lexer)
	{
		lexer->value = remove_quotes_from_tok(lexer->value);
		lexer = lexer->next;
	}
}
