/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:00:24 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/30 09:18:24 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Extract the environment variable key starting at position *i in token.*/

static char	*expand_env_key(const char *token, int *i)
{
	int		start;
	char	*key;

	start = *i;
	while (ft_isalnum(token[*i]) || token[*i] == '_')
		(*i)++;
	key = ft_substr(token, start, *i - start);
	return (key);
}

/*Append the environment variable value to the existing result string.*/

static char	*expand_env_value(char *res, const char *val)
{
	char	*dup;
	char	*result;

	dup = ft_strdup(val);
	if (!dup)
		return (NULL);
	if (!res)
		return (dup);
	result = ft_strjoin_ctr_free(res, dup, 3);
	return (result);
}

/*Handle invalid dollar expansions by advancing index without appending.*/

static char	*handle_invalid_dollar(char *res, const char *token, int *i)
{
	if (token[*i])
		(*i)++;
	return (res);
}

/*Append the last exit code value to the result string.*/

static char	*handle_exit_code(char *res, int *i, t_shell *shell)
{
	char	*val;
	char	*joined;

	val = ft_itoa(shell->tmp_exit_code);
	if (!val)
		return (NULL);
	(*i)++;
	if (!res)
		return (val);
	joined = ft_strjoin_ctr_free(res, val, 3);
	return (joined);
}

/*Process and expand a dollar sign variable in the token,
appending its value to res.*/

char	*join_dollar(char *res, const char *token, int *i, t_shell *shell)
{
	char	*key;
	char	*val;

	(*i)++;
	if (token[*i] == '?')
		return (handle_exit_code(res, i, shell));
	if (!ft_isalpha(token[*i]) && token[*i] != '_')
		return (handle_invalid_dollar(res, token, i));
	key = expand_env_key(token, i);
	if (!key)
		return (NULL);
	val = get_env_value(shell->env, key);
	free(key);
	if (!val)
		return (res);
	return (expand_env_value(res, val));
}
