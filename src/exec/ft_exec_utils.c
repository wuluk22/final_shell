/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:08:47 by clegros           #+#    #+#             */
/*   Updated: 2024/06/15 11:08:48 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ltrim(char *str)
{
	while (isspace((unsigned char)*str))
		str++;
	return (str);
}

static char	*rtrim(char *str)
{
	char	*end;

	end = str + strlen(str) - 1;
	while (end >= str && isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

char	*ft_trim(char *str)
{
	return (rtrim(ltrim(str)));
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

void	ft_open_file(t_cmds *cmd, int sv_stdin, int fd, int nb)
{
	if (nb == 0)
		fd = open(ft_trim(cmd->redirections->next->token),
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (nb == 1)
		fd = open(ft_trim(cmd->redirections->next->token),
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (nb == 2)
		fd = open(ft_trim(cmd->redirections->next->token),
				O_RDONLY, 0777);
	if (nb == 3)
	{
		fd = open(".feuys.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
		dup2(sv_stdin, 0);
		ft_here_txt(cmd, ft_trim(cmd->redirections->next->token), fd);
		close(fd);
		fd = open(".feuys.txt", O_RDONLY, 0777);
		dup2(fd, 0);
		close(fd);
	}
	if (nb == 0 || nb == 1)
		dup2(fd, 1);
	if (nb == 2)
		dup2(fd, 0);
	if (nb == 3)
		dup2(STDOUT_FILENO, 1);
}
