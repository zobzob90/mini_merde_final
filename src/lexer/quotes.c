/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:34:42 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/10 10:49:55 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return 1 if single quote, 2 if double quote, 0 otherwise.*/

int	is_quote(const char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

/*Check for unmatched opening quotes in the string
and return quote type if unclosed.*/

int	check_opened_quotes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (quote == 0)
				quote = is_quote(str[i]);
			else if (quote == is_quote(str[i]))
				quote = 0;
		}
		i++;
	}
	return (quote);
}

/*Print error message if quotes are unclosed; return 0 if error, 1 if OK.*/

int	check_closed_quotes(char *str)
{
	int	quote;

	quote = check_opened_quotes(str);
	if (quote != 0)
	{
		if (quote == 1)
			ft_putstr_fd("Error: Unclosed single quote\n", 2);
		else if (quote == 2)
			ft_putstr_fd("Error: Unclosed double quote\n", 2);
		return (0);
	}
	return (1);
}

/*Return a new string with all surrounding quotes
removed (preserving literal characters).*/

char	*remove_quotes_from_tok(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*new_str;

	i = 0;
	j = 0;
	quote = 0;
	new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (!quote && is_quote(str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	if (str)
		free(str);
	return (new_str);
}
