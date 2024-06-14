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

static int	process_command(char *line, t_env **n_envp)
{
	t_lexer			*lexer_list;
	t_simple_cmds	*cmd_list;

	lexer_list = NULL;
	cmd_list = NULL;
	if (!line)
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
		else if (ft_strncmp(cmd_list->str[0], "export", 6) == 0)
		{
			*n_envp = ft_export(cmd_list, *n_envp);
			return (0);
		}
		else
			command_executer(cmd_list->str, cmd_list, n_envp);
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

void	minishell_loop(char *line, char **envp)
{
	t_env	*n_envp;

	n_envp = malloc(sizeof(t_env *));
	n_envp = ft_init_envp(envp, n_envp);
	ft_transform(n_envp);
	while (1)
	{
		ft_set_input_signals();
		line = readline("\033[5m<-\033[0;35m(-x _ x-) \033[1;3;5;45mmini\033[1;3;5;37;45mshell\033[0;5m->\033[0m ");
		if (!line)
			break ;
		add_history(line);
		if (process_command(line, &n_envp))
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	line = malloc(sizeof(char *));
	line = NULL;
	minishell_loop(line, envp);
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
