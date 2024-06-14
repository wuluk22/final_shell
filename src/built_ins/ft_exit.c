/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:13 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:41:04 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parcour(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_is_strnum(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_simple_cmds *cmd)
{
	int	ret;

	if (parcour(cmd->str) == 1)
	{
		exit(g_exit_global);
		return (0);
	}
	else if (parcour(cmd->str) == 2 || !ft_is_strnum(cmd->str[1]))
	{
		if (ft_is_strnum(cmd->str[1]))
		{
			ret = ft_atoi(cmd->str[1]);
			exit(ret);
			return (0);
		}
		else
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit(255);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
}
