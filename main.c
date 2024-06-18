/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:04:56 by clegros           #+#    #+#             */
/*   Updated: 2024/06/18 17:36:57 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#define MEOW "\033[5m<-\033[0;35m(-x _ x-)"
#define MIAO " \033[1;3;5;45mmini\033[1;3;5;37;45mshell\033[0;5m->\033[0m "

static void	ft_free_envp(t_env *n_envp)
{
	t_env	*current;
	t_env	*next;

	current = n_envp;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
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
	{
		ft_cleanup_cmd_list(cmd_list);
		ft_free_list(lexer_list);
		return (1);
	}
	ft_cleanup_cmd_list(cmd_list);
	ft_free_list(lexer_list);
	return (0);
}

static void	minishell_loop(t_env *n_envp, char *line)
{
	while (1)
	{
		ft_set_input_signals();
		line = readline(MEOW MIAO);
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
	ft_free_envp(n_envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*n_envp;
	t_env	*head;

	head = NULL;
	n_envp = NULL;
	n_envp = malloc(sizeof(t_env));
	if (!n_envp)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	n_envp->key = NULL;
	n_envp->value = NULL;
	n_envp->next = NULL;
	n_envp->env = NULL;
	n_envp = ft_init_envp(n_envp, head, envp, -1);
	(void)argc;
	(void)argv;
	line = NULL;
	minishell_loop(n_envp, line);
	return (EXIT_SUCCESS);
}
