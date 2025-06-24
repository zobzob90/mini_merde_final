/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:32 by vdeliere          #+#    #+#             */
/*   Updated: 2025/06/20 15:49:57 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Generate a random name for the heredoc's temporary file.*/

char	*generate_tmp_filename(void)
{
	char			*base;
	char			*num;
	char			*name;
	int				random_fd;
	unsigned int	rand_val;

	base = ".heredoc_tmp_";
	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd < 0)
		return (NULL);
	if (read(random_fd, &rand_val, sizeof(rand_val)) < 0)
	{
		close(random_fd);
		return (NULL);
	}
	close(random_fd);
	rand_val = rand_val % 100000;
	num = ft_itoa(rand_val);
	if (!num)
		return (NULL);
	name = ft_strjoin(base, num);
	free(num);
	return (name);
}

/*Copy the heredoc content in a temporary file.*/

static int	write_heredoc_file(const char *filename, const char *limiter, t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc open"), 1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		line = expand_token(line, shell);
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

/*Return 1 when the heredoc creation fails and 0 when it's OK.*/

int	setup_heredocs(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;
	char	*filename;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				filename = generate_tmp_filename();
				if (!filename || write_heredoc_file(filename, redir->file, shell))
					return (1);
				free(redir->file);
				redir->file = filename;
				redir->type = REDIR_IN;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

/*Remove temporary heredoc files from all commands.*/

void	cleanup_heredocs(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == REDIR_IN && redir->file
				&& !ft_strncmp (redir->file, ".heredoc_tmp_", 13))
				unlink(redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
