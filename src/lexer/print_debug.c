/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:16:44 by ertrigna          #+#    #+#             */
/*   Updated: 2025/05/19 13:25:57 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Free all memory associated with the lexer linked list.*/

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

/*Print each token in the lexer list with its corresponding type.*/

void	print_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type == WORD)
			printf("WORD: %s\n", lexer->value);
		else if (lexer->type == PIPE)
			printf("PIPE\n");
		else if (lexer->type == REDIR_IN)
			printf("REDIRECT IN\n");
		else if (lexer->type == REDIR_OUT)
			printf("REDIRECT OUT\n");
		else if (lexer->type == APPEND)
			printf("APPEND\n");
		else if (lexer->type == HEREDOC)
			printf("HEREDOC\n");
		lexer = lexer->next;
	}
}
