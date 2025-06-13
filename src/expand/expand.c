/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:47 by valentin          #+#    #+#             */
/*   Updated: 2025/06/13 11:38:23 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contains_expand_chars(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '$' || *str == '\'' || *str == '\"')
			return (1);
		str++;
	}
	return (0);
}

static char	*expand_token(char *token, t_shell *shell)
{
	char	*res;
	int		i;
	int		len;

	len = ft_strlen(token);
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (token[i] == '\'')
			res = join_literal(res, token, &i);
		else if (token[i] == '\"')
			res = join_double_quote(res, token, &i, shell);
		else if (token[i] == '$' && token[i + 1] != '\0')
			res = join_dollar(res, token, &i, shell);
		else
			res = join_char(res, token[i++]);
		if (!res)
			return (NULL);
	}
	return (res);
}

void	expand_all_tokens(t_lexer *lexer, t_shell *shell)
{
	char	*new;

	while (lexer)
	{
		if (lexer && lexer->value && contains_expand_chars(lexer->value))
		{
			new = expand_token(lexer->value, shell);
			if (!new)
				return ;
			free(lexer->value);
			lexer->value = new;
		}
		lexer = lexer->next;
	}
}
