/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:04:56 by clegros           #+#    #+#             */
/*   Updated: 2024/05/31 12:39:29 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*static void	init(char *args, t_lexer *lexer_list, t_simple_cmds *cmd_list)
{
	tokenize(args, &lexer_list);
	lexer_to_cmds(&lexer_list, &cmd_list);
	if (cmd_list)
		expander(cmd_list);
}*/

/*static void	null(char *args, char *line, t_simple_cmds *cmd_list)
{
	args = NULL;
	line = NULL;
	while (cmd_list)
	{
		cmd_list->str = NULL;
		cmd_list = cmd_list->next;
	}
}
*/


static void	cleanup_cmd_list(t_simple_cmds *cmd_list)
{
	t_simple_cmds	*temp;

	while (cmd_list)
	{
		if (cmd_list->str)
			free(cmd_list->str);
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free(temp);
	}
}

static int	process_command(char *line, char **envp, char **env_p, t_env *envpp)
{
	t_lexer			*lexer_list;
	t_simple_cmds	*cmd_list;

	lexer_list = NULL;
	cmd_list = NULL;
	if (!line | !envp | !env_p)
	{
		perror("error reading command");
		return (0);
	}
	tokenize(line, &lexer_list);
	lexer_to_cmds(&lexer_list, &cmd_list);
	//write(1, cmd_list->str[1], ft_strlen(cmd_list->str[1]));
	//write(1, "\n", 1);
	if (cmd_list)
		expander(cmd_list);
	//cmd_list->envp = env_p;
	if (cmd_list && cmd_list->str)
	{
		if (ft_strncmp(cmd_list->str[0], "exit", 4) == 0)
		{
			if (ft_exit(cmd_list) != 1)
			{
				cleanup_cmd_list(cmd_list);
				free_list(lexer_list);
				return (1);
			}
		}
		else
			command_executer(cmd_list->str, envp, cmd_list, env_p, envpp);
	}
	/*t_env *current = env_list;
    while (current) {
        t_env *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }*/
	cleanup_cmd_list(cmd_list);
	free_list(lexer_list);
	return (0);
}

void	minishell_loop(char *line, char **envp, char **env)
{
	char	**env_p;
	t_env	*envpp;
	size_t	envp_len;
	size_t	i;

	i = 0;
	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	env_p = malloc(sizeof(char *) * (sizeof(envp) / sizeof(envp[0])));
	envpp = malloc(sizeof(t_env));
	envpp->env = malloc((envp_len + 1) * sizeof(char *));
	if (!env_p | !envpp | !envpp->env)
	{
		free(envpp);
		return ;
	}
	while (i < envp_len) 
	{
		envpp->env[i] = ft_strdup(envp[i]);
		i++;
	}
	envpp->env[envp_len] = NULL;
	env_p = envp;
	(void)env;
	while (1)
	{
		ft_set_input_signals();
		line = readline("\033[5m<-\033[0;35m(-x _ x-) \033[1;3;5;45mmini\033[1;3;5;37;45mshell\033[0;5m->\033[0m ");
		if (!line)
			break ;
		add_history(line);
		if (process_command(line, envp, env_p, envpp))
		{
			free(line);
			break ;
		}
		if (line)
			free(line);
		//g_exit_global = 0;
	}
}

/*void	minishell_loop(char *line, char **envp)
{
	t_lexer			*lexer_list;
	t_simple_cmds	*cmd_list;
	char			*args;

	cmd_list = malloc(sizeof(t_simple_cmds));
	(void)envp;
	lexer_list = NULL;
	cmd_list = NULL;
	while (1)
	{
		ft_set_input_signals();
		line = readline("minishell>> ");
		if (!line)
			break ;
		add_history(line);
		args = line;
		tokenize(args, &lexer_list);
		lexer_to_cmds(&lexer_list, &cmd_list);
		if (cmd_list)
			expander(cmd_list);
		if (cmd_list)
			if (cmd_list->str)
				command_executer(cmd_list->str, envp, cmd_list);
		args = NULL;
		line = NULL;
		while (cmd_list)
		{
			cmd_list->str = NULL;
			cmd_list = cmd_list->next;
		}
	}
}*/

int	main(int argc, char **argv, char **envp, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	line = malloc(sizeof(char *));
	line = NULL;
	minishell_loop(line, envp, env);
	return (EXIT_SUCCESS);
}

/*
	t_lexer			*redir;
	int				i;
		while (cmd_list != NULL)
		{
			i = 0;
			printf("\n\nCommand:\n");
			while (cmd_list->str[i] != NULL)
			{
				printf("  %s\n", cmd_list->str[i]);
				i++;
			}
			printf("\n\nRedirections:\n");
			redir = cmd_list->redirections;
			while (redir != NULL)
			{
				printf("  %s\n", redir->token);
				redir = redir->next;
			}
			cmd_list = cmd_list->next;
		}
		free_list(lexer_list);
		free_cmds(cmd_list);
		while (list)
		{
			printf("f0ff----%s|%d|%s\n", list->str, list->i, list->chr);
			list = list->next;
		}
		if (strcmp(list.cmd, "exit") == 0)
			break ;
		system("leaks ./minishell");
*/
