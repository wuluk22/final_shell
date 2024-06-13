/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:51:32 by clegros           #+#    #+#             */
/*   Updated: 2024/05/14 15:51:35 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include "../utils/get_next_line/ft_get_next_line.h"
# include "../utils/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 
# endif

# define DOUBLE_QUOTE '"'
# define SINGLE_QUOTE '\''

int	g_exit_global;

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	//DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_lexer
{
	char				*str;
	char				*token;
	char				*chr;
	int					i;
//	enum				e_token;
//	enum				e_state;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_utils
{
	char	*args;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	t_lexer	*lexer;
}	t_utils;

typedef struct s_parser
{
	char			**str;
	int				num_red;
	char			*hd_file_name;
	t_lexer			*redirect;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

typedef struct s_env {
	//int				export;
	char			*key;
	char			*value;
	struct s_env	*next;
	char			**env;
}	t_env;

typedef struct	s_tools
{

}	t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	char					*builton;
	int						num_redirections;
	int						p_fd_input[2];
	int						p_fd_output[2];
	pid_t					pid;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
	t_env					*envp;
	int						exit;
}	t_simple_cmds;

//main
void			minishell_loop(char *line, char **envp);
char			*trim(char *str);

//signals
void			ft_signal_handler(int sign);
void			ft_set_input_signals(void);

//exec
void			error(void);
void			ft_append(char *args[], char *envp[]);
int				ft_meta(char *c);
int				list_parkour(t_lexer *list);
void			ft_first_iter(char *args[], char *envp[]);
int				ft_stacklen(t_lexer *list);
void			command_executer(char **args, t_simple_cmds *list, t_env *n_envp);
void			ft_heredoc(char *args[], char *envp[]);
void			ft_input(char *args[], char *envp[]);
char			*find_path(char **envp, t_pipex *pipex);
char			*parsing(char **cmd_paths, char *cmd_args);
void			ft_multi_pipe(int argc, t_simple_cmds *list, t_env *n_envp);
void			open_file(int fd, t_simple_cmds *cmd, int sv_stdin, int nb);
void			here_txt(char *limiter, t_simple_cmds *cmd, int fd);
char			*get_path(char *cmd, char **envp);
char			*ft_strnstr(const char *find, const char *to_find, size_t len);
void			ft_redir(char *args[], char *envp[]);
void			parent_free(t_pipex *pipex);
void			child_free(t_pipex *pipex);
t_pipex			ft_dispatch(t_pipex exec, char *arg);
int				ft_meta_str(char c);
int				list_parkour_str(char *list);
void			ft_meta_mgmt(char *cmd, char **envp);
t_env			*ft_init_envp(char **envp, t_env *n_envp);
char			**ft_transform(t_env *n_envp);

//expand
char			*get_env_value(const char *var_name);
int				count_occurrences(const char *str, const char *old_substr);
void			delete_quotes(char *str, char c);
char			*allocate_result(char *str, char *old_substr, char *new_substr);
char			*replace_substr(char *str, char *old_substr, char *new_substr);
int				expander(t_simple_cmds *cmd_list);

//lexer
void			free_list(t_lexer *list);
void			print_list(t_lexer *list);
void			add_token(t_lexer **list, char *token);
void			add_crt_token(t_lexer **list, char **tok_start, char *current);
void			handle_quotes(char crt_char, bool *in_quotes, char *crt_quote);
void			hdl_m(t_lexer **list, char **t_start, char **crt, bool *in_qts);
void			tokenize(char *cmd, t_lexer **list);
void			handle_dbl_greater(t_lexer **list, char **t_start, char **crt);
void			handle_dbl_less(t_lexer **list, char **t_start, char **crt);
void			handle_greater(t_lexer **list, char **t_start, char **current);
void			handle_less(t_lexer **list, char **token_start, char **current);
void			handle_pipe(t_lexer **list, char **token_start, char **current);

//parser
void			parser(t_lexer *list, t_parser *pars);
void			lexer_to_cmds(t_lexer **tokens, t_simple_cmds **cmd_list);
void			free_cmds(t_simple_cmds *cmds);
bool			is_builtin(char *command);
int				is_redirection_token(const char *token);
void			reverse_redirections_list(t_lexer **redirections);
t_simple_cmds	*create_simple_cmd_node(void);
void			add_spl_cmd(t_simple_cmds **cmd_list, t_simple_cmds *new_node);
void			handle_redirect_token(t_lexer **tokens, t_lexer **redirections,
					t_lexer **current, t_lexer **prev);
void			parse_redirect_tokens(t_lexer **tokens, t_lexer **redirections);
void			parse_redirections(t_lexer **tokens, t_lexer **redirections);
void			parse_command(t_lexer **tokens, t_simple_cmds **cmd_list);
char			*find_path(char **envp, t_pipex *pipex);
char			*parsing(char **cmd_paths, char *cmd_args);
void			parent_free(t_pipex *pipex);
void			child_free(t_pipex *pipex);

//built_ins
int				check_built_ins(char **str);
void			launch_b(char **str, t_simple_cmds *cmd, t_env *n_envp);
int				ft_echo(t_simple_cmds *cmd);
int				ft_cd(t_simple_cmds *cmd);
int				ft_pwd(t_simple_cmds *cmd);
t_env			*ft_export(t_simple_cmds *cmd, t_env *n_envp);
int				ft_unset(t_simple_cmds *cmd);
int				ft_env(t_simple_cmds *cmd, t_env *n_envp);
int				ft_exit(t_simple_cmds *cmd);

//utils
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);

#endif
