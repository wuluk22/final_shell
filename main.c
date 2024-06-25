/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:04:56 by clegros           #+#    #+#             */
/*   Updated: 2024/06/21 15:20:10 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#define MEOW "\033[5m<-\033[0;35m(-x _ x-)"
#define MIAO " \033[1;3;5;45mmini\033[1;3;5;37;45mshell\033[0;5m->\033[0m "

int	g_exit_global = 0;

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
t_cmds	*ft_trim_quotes_cmd(t_cmds *cmd)
{
	t_cmds	*head;
	int		i;
	char	*trimmed;

	head = cmd;
	while(cmd)
	{
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			//printf("-%s-\n", cmd->str[i]);
			trimmed = ft_strtrim(cmd->str[i], "\'");
			//printf("-%s-\n", trimmed);
			if (trimmed)
			{
				free(cmd->str[i]);
				cmd->str[i] = trimmed;
			}
			i++;
		}
		//if (cmd->next)
		cmd = cmd->next;
	}
	return (head);
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
		ft_expander(cmd_list, n_envp);
	ft_trim_quotes_cmd(cmd_list);
	if (ft_b_ins(cmd_list, lexer_list, n_envp) == 1)
	{
		ft_cleanup_cmd_list(cmd_list);
		ft_free_list(lexer_list);
		//printf("yo\n");
		return (0);
	}
	ft_cleanup_cmd_list(cmd_list);
	ft_free_list(lexer_list);
	return (0);
}

static void	minishell_loop(t_env *n_envp)
{
	char	*line;

	line = NULL;
	ft_set_input_signals();
	while (1)
	{
		line = ft_strdup(ft_trim(readline(MEOW MIAO)));
		if (!line)
			break ;
		if (ft_strncmp(line, "\r", ft_strlen(line) != 0))
			add_history(line);
		if (ft_process_command(&n_envp, line))
		{
			free(line);
			//printf("yo\n");
			break ;
		}
		//if (line)
		free(line);
	}
	//if (n_envp)
	ft_free_envp(n_envp);
}

int	main(int argc, char **argv, char **envp)
{
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
	minishell_loop(n_envp);
	return (EXIT_SUCCESS);
}
