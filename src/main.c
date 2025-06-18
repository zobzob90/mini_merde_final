/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:14:20 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/16 18:05:23 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

/*Initializes the shell structure with default values
and invalid pipe descriptors.*/

void	init_shell(t_shell *shell)
{
	shell->env = NULL;
	shell->lexer = NULL;
	shell->cmd = NULL;
	shell->input = NULL;
	shell->exit_code = 0;
	shell->drucker_mode = 0;
	shell->pipe_fd[0] = -2;
	shell->pipe_fd[1] = -2;
}

/*Sets or updates the shell input string,
freeing the previous one if different.*/

void	init_shell_input(t_shell *shell, char *input)
{
	if (!input)
		return ;
	if (shell->input && ft_strcmp(shell->input, input) == 0)
		return ;
	if (shell->input)
		free(shell->input);
	shell->input = ft_strdup(input);
	if (!shell->input)
		exit_clean_shell(shell, "Error\n");
}

/*Cleans up the shell and exits the program, printing an optional message.*/

void	exit_clean_shell(t_shell *shell, char *msg)
{
	int	tmp_exit_code;

	tmp_exit_code = g_last_exit_code;
	if (msg)
		ft_putstr_fd(msg, 2);
	if (shell)
	{
		clear_history();
		free_shell(shell);
	}
	rl_clear_history();
	exit(tmp_exit_code);
}

/*Runs the main interactive shell loop handling input,
parsing, execution, and cleanup.*/

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
			(add_history(input), init_shell_input(shell, input), lexer(shell));
			free(input);
			if (shell->lexer)
			{
				parser(shell);
				if (shell->exit_code != 258 && shell->exit_code != 2)
					exec_cmds(shell, shell->cmd);
				(free_pars(shell->cmd), shell->cmd = NULL);
				(free_lexer(shell->lexer), shell->lexer = NULL);
				shell->exit_code = 0;
			}
		}
	}
}

/*Entry point: initializes shell, environment, signals,
and starts the shell loop.*/

int	main(int ac, char *av[], char **envp)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
		printf("Error: Too many arguments\n");
	(init_shell(&shell), init_env(&shell, envp),
		set_signal_handlers(), init_shell_loop(&shell));
	exit_clean_shell(&shell, NULL);
	return (0);
}
