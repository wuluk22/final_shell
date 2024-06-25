/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:23:35 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:10:40 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_output(int i, char **str, int fd, int newline)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (newline == 0)
		write(fd, "\n", 1);
}

char	*ft_trim_quotes(char *str)
{
	size_t	len;

	if (str == NULL || *str == '\0')
		return (str);
	len = ft_strlen(str);
	while (len > 0 && (str[0] == '\'' || str[0] == '"'))
	{
		str++;
		len--;
	}
	while (len > 0 && (str[len - 1] == '\'' || str[len - 1] == '"'))
		str[--len] = '\0';
	return (str);
}

int	ft_echo(t_cmds *cmd)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 0;
	newline = 0;
	if (cmd->str[i] && ft_strncmp(cmd->str[i], "-n", 2) == 0)
	{
		newline = 1;
		i++;
	}
	else if (cmd->str[i] && ft_strncmp(cmd->str[i], "$", 1) == 0 && ft_strlen(cmd->str[i]) == 1)
	{
		write(1, "$", 1);
		return (EXIT_SUCCESS);
	}
	while (cmd->str[j])
	{
		cmd->str[j] = ft_trim_quotes(cmd->str[j]);
		cmd->str[j] = ft_trim(cmd->str[j]);
		j++;
	}
	ft_output(i, cmd->str, STDOUT_FILENO, newline);
	return (EXIT_SUCCESS);
}
