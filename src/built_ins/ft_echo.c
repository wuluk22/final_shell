/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:23:35 by clegros           #+#    #+#             */
/*   Updated: 2024/06/01 15:24:08 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void output(int i, char **str, int fd, int newline)
{
    while (str[i])
	{
        ft_putstr_fd(str[i], fd);
        if (str[i + 1])
		{
            ft_putstr_fd(" ", fd);
        }
        i++;
    }
    if (newline == 0)
	{
        write(fd, "\n", 1);
    }
}

char* trim_quotes(char* str) {
    if (str == NULL || *str == '\0') {
        return str;
    }

    size_t len = strlen(str);

    while (len > 0 && (str[0] == '\'' || str[0] == '"')) {
        str++;
        len--;
    }

    while (len > 0 && (str[len - 1] == '\'' || str[len - 1] == '"')) {
        str[--len] = '\0';
    }

    return str;
}

int	ft_echo(t_simple_cmds *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;

	if (cmd->str[i] && strcmp(cmd->str[i], "-n") == 0)
	{
		newline = 1;
		i++;
	}

	int j = 0;
	while (cmd->str[j])
	{
		cmd->str[j] = trim_quotes(cmd->str[j]);	
		cmd->str[j] = trim(cmd->str[j]);
		j++;
	}

	output(i, cmd->str, STDOUT_FILENO, newline);

	return (EXIT_SUCCESS);
}
