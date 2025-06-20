/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:51:22 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/20 15:50:37 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Open a file descriptor for the given redirection based on its type.*/

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

/*Duplicate oldfd to newfd, closing oldfd afterward, handling errors.*/

static int	dup_fd(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (0);
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		close(oldfd);
		return (1);
	}
	close(oldfd);
	return (0);
}

/*Open redirection file and update input/output fd variables accordingly.*/

static int	handle_redir_fd(t_redir *redir, int *fd_in, int *fd_out)
{
	int	fd;

	fd = open_redir_fd(redir);
	if (fd == -1)
		return (1);
	if (redir->type == REDIR_IN)
	{
		if (*fd_in != -1)
			close(*fd_in);
		*fd_in = fd;
	}
	else if (redir->type == REDIR_OUT || redir->type == APPEND)
	{
		if (*fd_out != -1)
			close(*fd_out);
		*fd_out = fd;
	}
	else
		close(fd);
	return (0);
}

/*Process all redirections: open files and redirect standard input/output.*/

int	handle_redir_exec(t_redir *redir)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	while (redir)
	{
		if (!redir->file)
			return (write(2, "Invalid redirection file\n", 25), 1);
		if (handle_redir_fd(redir, &fd_in, &fd_out))
			return (1);
		redir = redir->next;
	}
	if (fd_in != -1 && dup_fd(fd_in, STDIN_FILENO))
		return (1);
	if (fd_out != -1 && dup_fd(fd_out, STDOUT_FILENO))
		return (1);
	return (0);
}
