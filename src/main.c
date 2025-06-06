/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:14:20 by ertrigna          #+#    #+#             */
/*   Updated: 2025/05/27 14:50:11 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->env = NULL;
	shell->lexer = NULL;
	shell->cmd = NULL;
	shell->exit_code = 0;
	shell->input = NULL;
	shell->drucker_mode = 0;
	shell->pipe_fd[0] = -2;
	shell->pipe_fd[1] = -2;
}

void	init_shell_input(t_shell *shell, char *input)
{
	if (!input)
		return ;
	if (shell->input)
		free(shell->input);
	shell->input = ft_strdup(input);
	if (!shell->input)
		exit_clean_shell(shell, "Error\n");
}

void	exit_clean_shell(t_shell *shell, char *msg)
{
	int	tmp_exit_code;

	tmp_exit_code = shell->exit_code;
	if (msg)
		ft_putstr_fd(msg, 2);
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free_shell(shell);
	rl_clear_history();
	exit(tmp_exit_code);
}

static void	init_shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = get_prompt(shell);
		if (!input)
			exit_clean_shell(shell, "Allez, salut mon pote !👋\n");
		else
		{
			add_history(input);
			init_shell_input(shell, input);
			lexer(shell);
			if (shell->lexer)
			{
				parser(shell);
				exec_cmds(shell, shell->cmd, shell->env);
				(free_pars(shell->cmd), shell->cmd = NULL);
				(free_lexer(shell->lexer), shell->lexer = NULL);
			}
			free(input);
			if (shell->input)
				(free(shell->input), shell->input = NULL);
		}
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_shell	shell;

	(void)av;
	(void)envp;
	if (ac != 1)
		printf("Error: Too many arguments\n");
	(init_shell(&shell), init_env(&shell, envp),
		set_signal_handlers(), init_shell_loop(&shell));
	exit_clean_shell(&shell, NULL);
	return (0);
}
