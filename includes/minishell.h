/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:51:32 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 15:20:54 by yohanafi         ###   ########.fr       */
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

extern int	g_exit_global;

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	char			**env;
}	t_env;

typedef struct s_cmds
{
	char			**str;
	char			*builton;
	int				num_redirections;
	int				p_fd_input[2];
	int				p_fd_output[2];
	pid_t			pid;
	char			*hd_file_name;
	t_lexer			*redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	t_env			*envp;
	int				exit;
}	t_cmds;

//main
char	*ft_trim(char *str);
t_cmds	*ft_trim_quotes_cmd(t_cmds *cmd);

//signals
void	ft_signal_handler(int sign);
void	ft_set_input_signals(void);
void	ft_set_dfl_signal(void);

//exec
void	ft_error(void);
void	ft_close(int *fd);
void	ft_free_array(char **array);
char	*ft_free_tab(char **tabs);
void	ft_process(t_cmds *cmd, t_env **n_envp, int nb, int argc);
void	ft_exec(t_env *n_envp, char **cmd);
void	ft_handle_process(t_cmds *cmd, int nb, int argc);
void	ft_init_multi(t_cmds *list);
void	ft_free_multi(pid_t *pid, int last_exit);
void	ft_append(char *args[], char *envp[]);
int		ft_meta(char *c);
int		ft_list_parkour(t_lexer *list);
void	ft_first_iter(char *args[], char *envp[]);
int		ft_stacklen(t_lexer *list);
void	ft_command_exec(t_cmds *list, t_env **n_envp, char **args);
void	ft_heredoc(char *args[], char *envp[]);
void	ft_input(char *args[], char *envp[]);
char	*ft_parsing(char **cmd_paths, char *cmd_args);
void	ft_multi_pipe(t_cmds *list, t_env **n_envp, int argc, int j);
void	ft_open_file(t_cmds *cmd, int sv_stdin, int fd, int nb);
void	ft_txt(t_cmds *cmd, char *limiter, int fd);
char	*ft_get_path(char **envp, char *cmd);
char	*ft_strnstr(const char *find, const char *to_find, size_t len);
void	ft_redir(char *args[], char *envp[]);
void	ft_parent_free(t_pipex *pipex);
void	ft_child_free(t_pipex *pipex);
t_pipex	ft_ft_dispatch(t_pipex exec, char *arg);
int		ft_meta_str(char c);
int		ft_list_parkour_str(char *list);
void	ft_meta_mgmt(char **envp, char *cmd);
t_env	*ft_init_envp(t_env *n_envp, t_env *head, char **envp, int i);
char	**ft_transform(t_env *n_envp);
void	ft_check(t_cmds *cmd, int fd, int sv_stdin);
void	ft_parent(t_cmds *cmd, pid_t pid);
pid_t	ft_pipe(t_cmds *cmd, t_env **n_envp, int nb, int argc);
void	ft_pre_check_commands(t_cmds *list, t_env *n_envp);

//expand
char	*ft_get_env_value(t_env *n_envp, const char *var_name);
int		ft_count_occurrences(const char *str, const char *old_substr);
void	ft_delete_quotes(char *str, char c);
char	*ft_allocate_result(char *str, char *old_substr, char *new_substr);
char	*ft_replace_substr(char *str, char *old_substr, char *new_substr);
int		ft_expander(t_cmds *cmd_list, t_env **n_envp);
char	*ft_rep_env_var(t_env **n_envp, char *expanded_arg, char *dollar_pos);
char	*ft_expand_variable(t_env **n_envp, const char *arg);
char	*ft_replace_exit_status(char *expanded_arg);

//lexer
void	ft_free_list(t_lexer *list);
void	ft_print_list(t_lexer *list);
void	ft_add_token(t_lexer **list, t_lexer *new_token, const char *token);
void	ft_add_crt_token(t_lexer **list, char **tok_start, char *current);
void	ft_handle_quotes(char crt_char, char *crt_quote, bool *in_quotes);
void	ft_hdl_m(t_lexer **list, char **t_start, char **crt, bool *in_qts);
void	ft_tokenize(t_lexer **list, char *cmd);
void	ft_handle_dbl_greater(t_lexer **list, char **t_start, char **crt);
void	ft_handle_dbl_less(t_lexer **list, char **t_start, char **crt);
void	ft_handle_greater(t_lexer **list, char **t_start, char **current);
void	ft_handle_less(t_lexer **list, char **token_start, char **current);
void	ft_handle_pipe(t_lexer **list, char **token_start, char **current);

//parser
void	ft_parser(t_parser *pars, t_lexer *list);
void	ft_lexer_to_cmds(t_cmds **cmd_list, t_lexer **tokens);
void	ft_free_cmds(t_cmds *cmds);
bool	ft_is_builtin(char *command);
int		ft_is_redirection_token(const char *token);
void	ft_reverse_redirections_list(t_lexer **redirections);
t_cmds	*ft_create_simple_cmd_node(void);
void	ft_add_spl_cmd(t_cmds **cmd_list, t_cmds *new_node);
void	ft_handle_redirect_token(t_lexer **tokens, t_lexer **redirections,
			t_lexer **current, t_lexer **prev);
void	ft_parse_redirect_tokens(t_lexer **tokens, t_lexer **redirections);
void	ft_parse_redirections(t_lexer **tokens, t_lexer **redirections);
void	ft_parse_command(t_cmds **cmd_list, t_lexer **tokens);
char	*ft_find_path(t_pipex *pipex, char **envp);
char	*ft_parsing(char **cmd_paths, char *cmd_args);
void	ft_parent_free(t_pipex *pipex);
void	ft_child_free(t_pipex *pipex);

//built_ins
int		ft_check_built_ins(char **str);
void	ft_launch_b(t_cmds *cmd, t_env **n_envp, char **str);
int		ft_echo(t_cmds *cmd);
t_env	*ft_cd(t_cmds *cmd, t_env *n_envp);
int		ft_pwd(t_cmds *cmd);
t_env	*ft_export(t_cmds *cmd, t_env *n_envp);
t_env	*ft_unset(t_cmds *cmd, t_env *n_envp);
int		ft_env(t_cmds *cmd, t_env *n_envp);
int		ft_exit(t_cmds *cmd);
int		ft_b_ins(t_cmds *cmd_list, t_lexer *lexer_list, t_env **n_envp);

//utils
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_cleanup_cmd_list(t_cmds *cmd_list);
char	*ft_trim_quotes(char *str);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strstr(const char *haystack, const char *needle);

#endif
