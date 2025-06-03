/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:18 by valentin          #+#    #+#             */
/*   Updated: 2025/06/03 15:39:48 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_literal(char *res, const char *token, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	res = ft_strjoin_free(res, ft_substr(token, start, *i - start));
	if (token [*i])
		(*i)++;
	return (res);
}

char	*join_dollar(char *res, const char *token, int *i, t_env *env)
{
	char	*key;
	char	*val;
	int		start;

	(*i)++;
	start = *i;
	while (ft_isalnum(token[*i]) || token[*i] == '_')
		(*i)++;
	key = ft_substr(token, start, *i - start);
	val = get_env_value(env, key);
	free(key);
	if (!val)
		return (NULL);
	return (ft_strjoin_free(res, val));
}

char	*join_char(char *res, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(res, ft_strdup(tmp)));
}

char	*join_double_quote(char *res, const char *token, int *i, t_env *env)
{
	(*i)++;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
			res = join_dollar(res, token, i, env);
		else
			res = join_char(res, token[(*i)++]);
	}
	if (token[*i])
		(*i)++;
	return (res);
}
