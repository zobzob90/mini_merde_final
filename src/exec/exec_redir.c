/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:51:22 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/05 11:53:56 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_fd(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		write(2, "Unknown redirection type\n", 26);
		return (-1);
	}
	if (fd == -1)
		perror(redir->file);
	return (fd);
}

int	handle_redir_exec(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (!redir->file)
			return (write(2, "Invalid redirection file\n", 25), 1);
		fd = open_redir_fd(redir);
		if (fd == -1)
			return (1);
		if (redir->type == REDIR_IN)
		{
			if (dup2(fd,STDIN_FILENO) == -1)
				return (close(fd), perror("dup2"), 1);
		}
		else
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (close(fd), perror("dup2"), 1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
