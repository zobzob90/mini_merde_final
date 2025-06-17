/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:58:45 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/16 17:47:17 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Initialize a t_cmd struct with default NULL values.*/

void	init_cmd(t_cmd *cmd)
{
	cmd->cmds = NULL;
	cmd->cmd_path = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->redir = NULL;
}

/*Initialize a t_redir struct with default values.*/

void	init_redir(t_redir *redir)
{
	redir->type = 0;
	redir->file = NULL;
	redir->next = NULL;
}

/*Allocate and initialize a new t_cmd; return pointer or NULL on failure.*/

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_putstr_fd("Error: Malloc failed in new_cmd\n", 2);
		return (NULL);
	}
	init_cmd(cmd);
	return (cmd);
}

/*Allocate and initialize a new t_redir; return pointer or NULL on failure.*/

t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		ft_putstr_fd("Error: Malloc failed in new_redir\n", 2);
		return (NULL);
	}
	init_redir(redir);
	return (redir);
}

/*void	print_pars(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;
	int		cmd_count = 0;

	while (cmd)
	{
		printf("=== Command %d ===\n", ++cmd_count);
		if (cmd->cmds)
		{
			i = 0;
			while (cmd->cmds[i])
			{
				printf("Arg[%d]: %s\n", i, cmd->cmds[i]);
				i++;
			}
		}
		else
			printf("No arguments\n");
		redir = cmd->redir;
		while (redir)
		{
			printf("Redirection: ");
			if (redir->type == REDIR_IN)
				printf("< ");
			else if (redir->type == REDIR_OUT)
				printf("> ");
			else if (redir->type == APPEND)
				printf(">> ");
			else if (redir->type == HEREDOC)
				printf("<< ");
			else
				printf("? ");
			printf("%s\n", redir->file);
			redir = redir->next;
		}
		if (cmd->next)
			printf("-> PIPE to next command\n");
		cmd = cmd->next;
	}
}*/
