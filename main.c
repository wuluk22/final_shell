/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:04:56 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:21:51 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (cmd_list)
		expander(cmd_list);
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
		else if (ft_strncmp(cmd_list->str[0], "unset", 5) == 0)
		{
			*n_envp = ft_unset(cmd_list, *n_envp);
			return (0);
		}
		else if (ft_strncmp(cmd_list->str[0], "cd", 2) == 0)
		{
			*n_envp = ft_cd(cmd_list, *n_envp);
			return (0);
		}
		else
			command_executer(cmd_list->str, cmd_list, n_envp);
	}
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
	}
}

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
//system("leaks ./minishell");
