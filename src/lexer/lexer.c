/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:19:53 by ertrigna          #+#    #+#             */
/*   Updated: 2025/05/19 13:26:17 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operator(t_shell *shell, t_lexer **lexer, char *input, int i)
{
	t_token	type;

	type = 0;
	if (is_pipe(input[i]))
	{
		type = PIPE;
		add_new_token(lexer, shell, type);
		return (i + 1);
	}
	else
	{
		type = is_redir(input, i);
		if (type)
		{
			add_new_token(lexer, shell, type);
			if (type == REDIR_IN || type == REDIR_OUT)
				return (i + 1);
			else
				return (i + 2);
		}
	}
	return (i);
}

static int	extract_world_len(t_shell *shell, char *input, int start)
{
	int		j;
	char	quote;

	j = 0;
	while (input[start + j]
		&& !is_space(input[start + j])
		&& !is_pipe(input[start + j]) && !is_redir(input, start + j))
	{
		if (is_quote(input[start + j]))
		{
			quote = input[start + j++];
			while (input[start + j] && input[start + j] != quote)
				j++;
			if (!input[start + j])
				exit_clean_shell(shell, "Error: Unclosed quote\n");
			j++;
		}
		else
			j++;
	}
	return (j);
}

static int	handle_word(t_shell *shell, t_lexer **lexer, char *input, int i)
{
	int		len;
	char	*word;
	char	*clean;

	len = extract_world_len(shell, input, i);
	word = ft_substr(input, i, len);
	if (!word)
		exit_clean_shell(shell, "Error in malloc word\n");
	clean = remove_quotes_from_tok(word);
	free(word);
	if (!clean)
		exit_clean_shell(shell, "Error in remove_quotes_from_tok\n");
	add_new_word(lexer, shell, clean);
	free(clean);
	return (i + len);
}

void	lexer(t_shell *shell)
{
	int		i;
	t_lexer	*lexer;
	char	*input;

	i = 0;
	lexer = NULL;
	input = shell->input;
	if (!check_closed_quotes(input))
		return ;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_pipe(input[i]) || is_redir(input, i))
			i = handle_operator(shell, &lexer, input, i);
		else
			i = handle_word(shell, &lexer, input, i);
	}
	if (!check_redir_syntax(lexer))
	{
		free_lexer(lexer);
		shell->lexer = NULL;
		return ;
	}
	shell->lexer = lexer;
}
