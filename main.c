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
#define MEOW "\033[5m<-\033[0;35m(-x _ x-) \033[1;3;5;45mmini\033[1;3;5;37;45mshell\033[0;5m->\033[0m "

void	ft_cleanup_cmd_list(t_cmds *cmd_list)
{
	t_cmds	*temp;

	while (cmd_list)
	{
		if (cmd_list->str)
			free(cmd_list->str);
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free(temp);
	}
}

static int	ft_process_command(t_env **n_envp, char *line)
{
	t_lexer	*lexer_list;
	t_cmds	*cmd_list;

	lexer_list = NULL;
	cmd_list = NULL;
	if (!line)
	{
		perror("error reading command");
		return (0);
	}
	ft_tokenize(&lexer_list, line);
	ft_lexer_to_cmds(&cmd_list, &lexer_list);
	if (cmd_list)
		ft_expander(cmd_list);
	if (ft_b_ins(cmd_list, lexer_list, n_envp) == 1)
		return (1);
	ft_cleanup_cmd_list(cmd_list);
	ft_free_list(lexer_list);
	return (0);
}

void	minishell_loop(char **envp, char *line)
{
	t_env	*n_envp;

	n_envp = malloc(sizeof(t_env *));
	n_envp = ft_init_envp(n_envp, envp);
	ft_transform(n_envp);
	while (1)
	{
		ft_set_input_signals();
		line = readline(MEOW);
		if (!line)
			break ;
		add_history(line);
		if (ft_process_command(&n_envp, line))
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
	minishell_loop(envp, line);
	return (EXIT_SUCCESS);
}
//system("leaks ./minishell");
