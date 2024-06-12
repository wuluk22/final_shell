/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:06 by clegros           #+#    #+#             */
/*   Updated: 2024/06/05 16:44:28 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_meta(char *c)
{
	if (strcmp(c, "|") == 0)
		return (1);
	if (strcmp(c, "<") == 0)
		return (2);
	if (strcmp(c, ">") == 0)
		return (3);
	if (strcmp(c, "<<") == 0)
		return (4);
	if (strcmp(c, ">>") == 0)
		return (5);
	else
		return (0);
}

/*void	execute_command(char **envp, char **args)
{
	pid_t	pid;
	int		status;
	char	**arg;

	if (list_parkour_str(args) >= 1)
		ft_meta_mgmt(args, envp);
	else
	{

	pid = fork();
	(void)envp;
	arg = args;
	//printf("---%s\n", *arg);
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		while (arg)
		{
			if (execve(exec.cmd, arg, NULL) == -1)
			{
				perror("Error executing command");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
		wait(&status);
}*/

int	list_parkour(t_lexer *list)
{
	t_lexer	*head;
	int		i;

	head = NULL;
	i = 0;
	while (list)
	{
		head = list;
		if (ft_meta(list->token) > 0)
			i++;
		list = list->next;
	}
	list = head;
	return (i);
}

/*
	ici il y a les differentes redirections, 
	il faut encore update les infos a leur envoyer
*/

void	ft_first_iter(char *args[], char *envp[])
{
	if (ft_meta(args[1]) == 2)
		ft_input(args, envp);
	else if (ft_meta(args[1]) == 3)
		ft_redir(args, envp);
	else if (ft_meta(args[1]) == 4)
		ft_heredoc(args, envp);
	else if (ft_meta(args[1]) == 5)
		ft_append(args, envp);
}

int	ft_stacklen(t_lexer *list)
{
	int		i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

/*
	
	-le premier if va dans le multi_pipe si
	il y a plus d'un element dans la liste
	( du coup si il y a au moins un pipe )

	-le else execute directement les commandes 
	simples comme "ls -la" ou "cat Makefile"

*/

void	command_executer(char **args, char **envp, t_simple_cmds *list, char **env_p)
{
	int				i;
	t_simple_cmds	*head;

	head = malloc(sizeof(t_simple_cmds));
	if (!head)
		return ;
	head = NULL;
	i = 0;
	(void)envp;
	(void)args;
	(void)env_p;
	if (list)
	{
		head = list;
		while (list)
		{
			if (list->next)
				list = list->next;
			else
				break ;
			i++;
		}
		list = head;
		ft_multi_pipe(i, list, list->envp);
	}
}
