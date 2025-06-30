/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:14:20 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/30 09:48:05 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;
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
	int	tmp;

	if (shell->exit_code != 0)
		tmp = shell->exit_code;
	else
		tmp = shell->tmp_exit_code;
	if (msg)
		ft_putstr_fd(msg, 2);
	if (shell)
		free_shell(shell);
	rl_clear_history();
	exit(tmp);
}

static void	reset_loop(t_shell *shell)
{
	if (shell->cmd)
		free_pars(shell->cmd);
	if (shell->lexer)
		free_lexer(shell->lexer);
	if (shell->input)
		free(shell->input);
	shell->cmd = NULL;
	shell->lexer = NULL;
	shell->input = NULL;
	shell->tmp_exit_code = shell->exit_code;
	shell->exit_code = 0;
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
		exit_sigint(shell);
		add_history(input);
		shell->input = ft_strdup(input);
		free(input);
		if (!shell->input)
			exit_clean_shell(shell, "malloc error: input\n");
		lexer(shell);
		if (shell->lexer)
			parser(shell);
		if (shell->cmd)
			exec_cmds(shell, shell->cmd);
		shell->tmp_exit_code = shell->exit_code;
		exit_sigint(shell);
		reset_loop(shell);
	}
}

/*Entry point: initializes shell, environment, signals,
and starts the shell loop.*/
int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
	{
		printf("Error: Too many arguments\n");
		return (1);
	}
	init_shell(&shell);
	init_env(&shell, envp);
	set_signal_handlers();
	init_shell_loop(&shell);
	exit_clean_shell(&shell, NULL);
	return (0);
}
