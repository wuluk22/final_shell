/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:06 by clegros           #+#    #+#             */
/*   Updated: 2024/06/18 16:36:07 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_meta(char *c)
{
	if (ft_strncmp(c, "|", 1) == 0)
		return (1);
	if (ft_strncmp(c, "<", 1) == 0)
		return (2);
	if (ft_strncmp(c, ">", 1) == 0)
		return (3);
	if (ft_strncmp(c, "<<", 2) == 0)
		return (4);
	if (ft_strncmp(c, ">>", 2) == 0)
		return (5);
	else
		return (0);
}

int	ft_list_parkour(t_lexer *list)
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

void	ft_command_exec(t_cmds *list, t_env **n_envp, char **args)
{
	int		i;
	t_cmds	*head;

	head = malloc(sizeof(t_cmds));
	head = NULL;
	i = 0;
	(void)args;
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
		ft_multi_pipe(list, n_envp, i, -1);
	}
}

void	ft_check(t_cmds *cmd, int fd, int sv_stdin)
{
	while (cmd->redirections->token != NULL)
	{
		if (!ft_strncmp(cmd->redirections->token, ">", 1)
			&& ft_strlen(cmd->redirections->token) == 1)
			ft_open_file(cmd, sv_stdin, fd, 0);
		if (!ft_strncmp(cmd->redirections->token, ">>", 2)
			&& ft_strlen(cmd->redirections->token) == 2)
			ft_open_file(cmd, sv_stdin, fd, 1);
		if (!ft_strncmp(cmd->redirections->token, "<", 1)
			&& ft_strlen(cmd->redirections->token) == 1)
			ft_open_file(cmd, sv_stdin, fd, 2);
		if (!ft_strncmp(cmd->redirections->token, "<<", 1)
			&& ft_strlen(cmd->redirections->token) == 2)
			ft_open_file(cmd, sv_stdin, fd, 3);
		if (cmd->redirections->next != NULL)
			cmd->redirections = cmd->redirections->next;
		else
			break ;
	}
}
