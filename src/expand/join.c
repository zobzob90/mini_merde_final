/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:32:18 by valentin          #+#    #+#             */
/*   Updated: 2025/06/13 11:42:13 by ertrigna         ###   ########.fr       */
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
	res = ft_strjoin_free(res, ft_substr(token, start, *i - start), 3);
	if (!res)
		return (NULL);
	if (token [*i])
		(*i)++;
	return (res);
}

static char	*handle_exit_code(char *res, int *i)
{
	char	*val;
	char	*joined;

	val = ft_itoa(g_last_exit_code);
	if (!val)
		return (NULL);
	(*i)++;
	if (!res)
		return (val);
	joined = ft_strjoin_free(res, val, 3);
	return (joined);
}

char	*join_dollar(char *res, const char *token, int *i, t_shell *shell)
{
	char	*key;
	char	*val;
	char	*val_dup;
	int		start;

	(*i)++;
	if (token[*i] == '?')
		return (handle_exit_code(res, i));
	start = *i;
	while (ft_isalnum(token[*i]) || token[*i] == '_')
		(*i)++;
	key = ft_substr(token, start, *i - start);
	if (!key)
		return (NULL);
	val = get_env_value(shell->env, key);
	free(key);
	if (!val)
		return (res);
	val_dup = ft_strdup(val);
	if (!val_dup)
		return (NULL);
	if (res)
		return (ft_strjoin_free(res, val_dup, 3));
	return (val_dup);
}

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
