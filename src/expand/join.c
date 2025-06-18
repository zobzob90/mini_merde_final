/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:18 by valentin          #+#    #+#             */
/*   Updated: 2025/06/16 17:46:57 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Append characters inside single quotes literally to res.*/

char	*join_literal(char *res, const char *token, int *i)
{
	int		start;
	char	*sub;

	(*i)++;
	start = *i;
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	sub = ft_substr(token, start, *i - start);
	if (!sub)
	{
		free(res);
		return (NULL);
	}
	res = ft_strjoin_free(res, sub);
	if (!res)
		return (NULL);
	if (token[*i])
		(*i)++;
	return (res);
}

/*Append a single character c to the res string.*/

char	*join_char(char *res, char c)
{
	char	tmp[2];
	char	*tmp_dup;
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	tmp_dup = ft_strdup(tmp);
	if (!tmp_dup)
		return (NULL);
	joined = ft_strjoin(res, tmp_dup);
	free(tmp_dup);
	if (!joined)
	{
		free(res);
		return (NULL);
	}
	free(res);
	return (joined);
}

/*Append characters inside double quotes to res,
expanding variables as needed.*/

char	*join_double_quote(char *res, const char *token, int *i, t_shell *shell)
{
	(*i)++;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$' && token[*i + 1]
			&& (ft_isalnum(token[*i + 1])
				|| token[*i + 1] == '?' || token[*i + 1] == '_'))
			res = join_dollar(res, token, i, shell);
		else
			res = join_char(res, token[(*i)++]);
		if (!res)
			return (NULL);
	}
	if (token[*i])
		(*i)++;
	return (res);
}
