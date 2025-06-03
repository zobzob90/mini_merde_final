/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:14:29 by ertrigna          #+#    #+#             */
/*   Updated: 2025/06/03 15:46:22 by ertrigna         ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../libft/libft.h"

# define PATH_MAX 4096
# define TRUE 1
# define FALSE 0

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
	int		exit_code;
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
char	*remove_quotes_from_tok(const char *str);
int		check_redir_syntax(t_lexer *lexer);
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
char	*join_dollar(char *res, const char *token, int *i, t_env *env);
char	*join_char(char *res, char c);
char	*join_double_quote(char *res, const char *token, int *i, t_env *env);
//char	*get_env_value(const char *name);
void	expand_all_tokens(t_lexer *lexer, t_env *env);

/*EXEC*/
int		exec_cmds(t_shell *shell, t_cmd *cmd, t_env *env);
int		handle_redir_exec(t_redir *redir);
void	wait_all_children(pid_t last_pid, int *status);
int		wait_and_return_status(pid_t pid);
int		exec_external(t_cmd *cmd, t_env *env);
void	exec_child(t_cmd *cmd, t_env *env, int prev_fd, int pipefd[2]);
int 	is_builtin(char *cmd);
int		exec_builtin_parent(t_cmd *cmd, t_shell *shell);

/*HEREDOC*/
int		setup_heredocs(t_cmd *cmd_list);
void	cleanup_heredocs(t_cmd *cmd_list);

/*REDIR*/
int		handle_redir_exec(t_redir *redir);

/*MAIN*/
void	init_shell(t_shell *shell);
void	init_shell_input(t_shell *shell, char *input);
void	exit_clean_shell(t_shell *shell, char *msg);

/*BUILTIN*/
int		get_echo(char **av);
int		get_exit(char **av);
int		get_cd(char **av);
int		get_pwd(char **av);
int		launch_built(t_shell *shell, char **argv);
int		get_unset(t_shell *shell, char **argv);

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

/*FREE*/
void	free_shell(t_shell *shell);
void	free_redir(t_redir *redir);
void	free_pars(t_cmd *cmd);
void	free_env(t_env *env);

/*UTILS*/
char	*ft_strjoin_3(const char *s1, const char *s2, const char *s3);
void	ft_sort_str_array(char **arr);

#endif 