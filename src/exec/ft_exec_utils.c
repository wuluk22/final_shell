/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:08:47 by clegros           #+#    #+#             */
/*   Updated: 2024/06/24 12:28:21 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ltrim(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

static char	*rtrim(char *str)
{
	char	*end;

	if (!str)
		return (NULL);
	end = str + ft_strlen(str) - 1;
	while (end >= str && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

char	*ft_trim(char *str)
{
	if (!str)
		return (NULL);
	return (rtrim(ltrim(str)));
}

static void	ft_hd_case(t_cmds *cmd, int sv_stdin, int fd)
{
	fd = open(".feuys.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	dup2(sv_stdin, 0);
	ft_txt(cmd, ft_trim(ft_trim_quotes(cmd->redirections->next->token)), fd);
	close(fd);
	fd = open(".feuys.txt", O_RDONLY, 0777);
	dup2(fd, 0);
	close(fd);
}

void	ft_open_file(t_cmds *cmd, int sv_stdin, int fd, int nb)
{
	if (nb == 0)
		fd = open(ft_trim(ft_trim_quotes(cmd->redirections->next->token)),
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (nb == 1)
		fd = open(ft_trim(ft_trim_quotes(cmd->redirections->next->token)),
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (nb == 2)
		fd = open(ft_trim(ft_trim_quotes(cmd->redirections->next->token)),
				O_RDONLY, 0777);
	if (nb == 3)
		ft_hd_case(cmd, sv_stdin, fd);
	if (nb == 0 || nb == 1)
	{
		dup2(fd, 1);
		close(fd);
	}
	if (nb == 2)
		dup2(fd, 0);
	if (nb == 3)
		dup2(STDOUT_FILENO, 1);
}
