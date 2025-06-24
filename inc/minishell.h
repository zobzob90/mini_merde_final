/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:14:29 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/24 14:47:25 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../libft/libft.h"

# define PATH_MAX 4096
# define MAX_PIPE 256
# define TRUE 1
# define FALSE 0

extern int	g_signal;

typedef enum e_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token;

typedef struct s_lexer
{
	char			*value;
	t_token			type;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_redir
{
	t_token			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmds;
	char			*cmd_path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_redir			*redir;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	t_lexer	*lexer;
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;
	int		exit_code;
	int		tmp_exit_code;
	int		drucker_mode;
	char	*input;
}	t_shell;

/*ENV*/
t_env	*new_node(char *env_str);
void	init_env(t_shell *shell, char **envp);
void	print_env(t_env *env);
void	free_env(t_env *env);
char	*get_env_value(t_env *env, const char *key);

/*LEXER*/
void	init_lexer(t_lexer *lexer);
void	add_new_token(t_lexer **lexer, t_shell *shell, t_token type);
void	add_new_word(t_lexer **lexer, t_shell *shell, char *value);
int		is_pipe(const char c);
int		is_space(const char c);
int		is_redir(const char *c, int i);
int		is_quote(const char c);
int		check_opened_quotes(char *str);
int		check_closed_quotes(char *str);
char	*remove_quotes_from_tok(char *str);
int		check_redir_syntax(t_shell *shell, t_lexer *lexer);
void	print_lexer(t_lexer *lexer);
void	free_lexer(t_lexer *lexer);
void	lexer(t_shell *shell);

/*PARSING*/
void	init_cmd(t_cmd *cmd);
void	init_redir(t_redir *redir);
t_cmd	*new_cmd(void);
t_redir	*new_redir(void);
t_redir	*redir_add_node(t_shell *shell, t_token type, char *file);
void	handle_redir(t_shell *shell, t_cmd *cmd, t_lexer *lex);
void	append_redir(t_redir **redir, t_redir *new);
void	append_cmd(t_shell *shell, t_cmd *cmd, char *input);
t_cmd	*append_pipe(t_shell *shell, t_cmd *cmd);
void	parser_syntax_error(t_shell *shell, const char *msg);
void	parser(t_shell *shell);
void	free_redir(t_redir *redir);
void	free_pars(t_cmd *cmd);

/*EXPANDER*/
char	*join_literal(char *res, const char *token, int *i);
char	*join_dollar(char *res, const char *token, int *i, t_shell *shell);
char	*join_char(char *res, char c);
char	*join_double_quote(char *res, const char *token,
			int *i, t_shell *shell);
char	*expand_token(char *token, t_shell *shell);
void	expand_all_tokens(t_lexer *lexer, t_shell *shell);

/*EXEC*/
int		exec_cmds(t_shell *shell, t_cmd *cmd);
int		handle_redir_exec(t_redir *redir);
void	wait_all_children(pid_t last_pid, int *status);
int		wait_and_return_status(pid_t pid);
int		check_exec_errors(char *path, t_cmd *cmd, t_shell *shell);
void	exec_external(t_cmd *cmd, t_shell *shell);
void	exec_child(t_cmd *cmd, t_shell *shell, int prev_fd, int pipefd[2]);
int		update_exit_code(t_shell *shell, int status);
int		is_builtin(char *cmd);
int		exec_builtin_parent(t_cmd *cmd, t_shell *shell);
int		env_list_size(t_env *env);
char	*ft_strjoin_path(char *path, char *cmd);
char	*resolve_cmd_path(char *cmd, t_env *env);
int		is_directory(const char *path);

/*EXEC_UTILS*/
char	**env_list_to_array(t_env *env);
int		exec_redir_only(t_cmd *cmd, t_shell *shell, int prev_fd);
int		exec_external_cmd(t_cmd *cmd, t_shell *shell,
			int *prev_fd, pid_t *last_pid);
int		try_exec_builtin(t_cmd *cmd, t_shell *shell);
int		handle_parent(pid_t pid, t_cmd *cmd, int *pipefd, int *prev_fd);
int		skip_empty_node(t_cmd **cmd);

/*HEREDOC*/
int		setup_heredocs(t_cmd *cmd_list, t_shell *shell);
void	cleanup_heredocs(t_cmd *cmd_list);

/*REDIR*/
int		handle_redir_exec(t_redir *redir);

/*MAIN*/
void	init_shell(t_shell *shell);
void	init_shell_input(t_shell *shell, char *input);
void	exit_clean_shell(t_shell *shell, char *msg);

/*BUILTIN*/
int		get_echo(char **av);
int		get_exit(char **av, t_shell *shell);
int		get_cd(t_shell *shell, char **av);
int		get_pwd(char **av);
int		get_export(t_shell *shell, char **argv);
int		launch_built(t_shell *shell, char **argv, t_cmd *cmd);
int		get_unset(t_shell *shell, char **argv);

/*BUILTIN EXPORT UTILS*/
t_env	*create_env_node(const char *key, const char *value, t_shell *shell);
void	add_or_update_env(t_env **env, char *key, char *value);
int		is_valid_export_key(const char *key);
char	*safe_trim(const char *str);
void	handle_key(t_env **env, char *arg, t_shell *shell);
void	handle_key_value(t_env **env, char *arg,
			char *equal_pos, t_shell *shell);
bool	export_args(t_env **env, char *arg, char *next_arg, t_shell *shell);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*EASTER*/
int		get_drucker(t_shell *shell);
int		get_hell(t_shell *shell);
int		get_jacquie(t_shell *shell);
int		get_shit(t_shell *shell);
char	*get_prompt(t_shell *shell);
int		get_reset(t_shell *shell);

/*SIGNAL*/
void	signal_handler(int signal);
void	set_signal_handlers(void);
void	exit_sigint(t_shell *shell);

/*FREE*/
void	free_shell(t_shell *shell);
void	free_redir(t_redir *redir);
void	free_pars(t_cmd *cmd);
void	free_env(t_env *env);

/*UTILS*/
int		print_cmd_not_found(t_shell *shell, char *cmd);
void	ft_sort_str_array(t_env	**arr, int size);

#endif 