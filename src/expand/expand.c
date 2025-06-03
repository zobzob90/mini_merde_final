/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:47 by valentin          #+#    #+#             */
/*   Updated: 2025/06/03 13:48:56 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*get_env_value(const char *name)
{
	char	*value;
	// int		len;
	// len = ft_strlen(name);
	// ft_printf("len = %d\n", len);
	value = getenv(name);
	ft_printf("%s\n", value);
	if (!value)
		return ("");
	else
		return (value);
}*/

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

static char	*expand_token(char *token, t_env *env)
{
	char	*res;
	int		i;

	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	i = 0;
	while (token && token[i])
	{
		if (token[i] == '\'')
			res = join_literal(res, token, &i);
		else if (token[i] == '\"')
			res = join_double_quote(res, token, &i, env);
		else if (token[i] == '$')
			res = join_dollar(res, token, &i, env);
		else
			res = join_char(res, token[i++]);
		if (!res)
			return (NULL);
	}
	return (res);
}

void	expand_all_tokens(t_lexer *lexer, t_env *env)
{
	char	*new;

	while (lexer)
	{
		if (lexer && lexer->value && contains_expand_chars(lexer->value))
		{
			new = expand_token(lexer->value, env);
			if (!new)
				return ;
			free(lexer->value);
			lexer->value = new;
		}
		lexer = lexer->next;
	}
}
