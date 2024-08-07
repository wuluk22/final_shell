/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:13 by clegros           #+#    #+#             */
/*   Updated: 2024/07/02 14:26:32 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_parcour(char **str)
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

static int	ft_handle_numeric_argument(char *arg)
{
	int	ret;

	if (ft_is_strnum(arg))
	{
		ret = ft_atoi(arg);
		exit(ret);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(255);
		return (0);
	}
}

static int	ft_parse_exit_arguments(char **args)
{
	if (ft_parcour(args) == 1)
	{
		exit(g_exit_global);
		return (0);
	}
	else if (ft_parcour(args) == 2 || !ft_is_strnum(args[1]))
		return (ft_handle_numeric_argument(args[1]));
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_global = 1;
		return (EXIT_FAILURE);
	}
}

int	ft_exit(t_cmds *cmd)
{
	int		i;
	t_cmds	*head;

	i = 0;
	head = cmd;
	while (head)
	{
		if (!ft_strncmp("exit", head->str[0], ft_strlen(head->str[0])))
			i++;
		head = head->next;
	}
	if (i >= 2)
		return (1);
	return (ft_parse_exit_arguments(cmd->str));
}
