/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:47 by valentin          #+#    #+#             */
/*   Updated: 2025/06/10 10:57:20 by ertrigna         ###   ########.fr       */
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

static char	*expand_token(char *token, t_shell *shell)
{
	char	*res;
	int		i;

	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	i = 0;
	while (token && token[i])
	{
		printf("Token[%d] = %c\n", i, token[i]);
		if (token[i] == '\'')
		{
			printf("I'm a simple quote\n");
			res = join_literal(res, token, &i);
		}
		else if (token[i] == '\"')
		{
			printf("I'm a double quote\n");
			res = join_double_quote(res, token, &i, shell);
		}
		else if (token[i] == '$')
		{
			printf("I'm a dollar\n");
			res = join_dollar(res, token, &i, shell);
		}
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
