/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:36:47 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/27 08:02:14 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Initialize a lexer node with default values.*/

void	init_lexer(t_lexer *lexer)
{
	lexer->value = NULL;
	lexer->type = WORD;
	lexer->next = NULL;
}

/*Allocate and append a new token of a given type to the lexer list.*/

void	add_new_token(t_lexer **lexer, t_shell *shell, t_token type)
{
	t_lexer	*new_token;
	t_lexer	*curr;

	new_token = malloc(sizeof(t_lexer));
	if (!new_token)
		exit_clean_shell(shell, "Error in malloc new_tok\n");
	new_token->value = NULL;
	new_token->type = type;
	if (!*lexer)
	{
		*lexer = new_token;
		new_token->next = NULL;
	}
	else
	{
		curr = *lexer;
		while (curr->next)
			curr = curr->next;
		curr->next = new_token;
		new_token->next = NULL;
	}
}

/*Allocate and append a new WORD token with a given value to the lexer list.*/

void	add_new_word(t_lexer **lexer, t_shell *shell, char *value)
{
	t_lexer	*new_token;
	t_lexer	*curr;

	new_token = malloc(sizeof(t_lexer));
	if (!new_token)
		exit_clean_shell(shell, "Error in malloc new_tok\n");
	new_token->value = ft_strdup(value);
	if (!new_token->value)
		exit_clean_shell(shell, "Error in dup new_tok->value\n");
	new_token->type = WORD;
	new_token->next = NULL;
	if (!*lexer)
		*lexer = new_token;
	else
	{
		curr = *lexer;
		while (curr->next)
			curr = curr->next;
		curr->next = new_token;
	}
}
