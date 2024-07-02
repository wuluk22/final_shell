/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_check_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:59:03 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/02 17:08:55 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_exit_command(t_cmds *list)
{
	if (ft_strncmp(list->str[0], "exit", ft_strlen(list->str[0])) == 0)
	{
		if (list->str[1] && list->str[2])
			g_exit_global = 1;
		return ;
	}
}

static void	handle_command_not_found(char *path, t_cmds *list)
{
	int	i;
	t_cmds	*head;

	i = 0;
	head = list;
	while (head)
	{
		if (!ft_strncmp("exit", head->str[0], ft_strlen(head->str[0])))
			i++;
		head = head->next;
	}
	if (path == NULL)
	{
		if ((!list->str[0] && !list->str[1] && list->redirections) || i >= 2)
		{
			g_exit_global = 0;
			return ;
		}
		g_exit_global = 127;
		ft_putstr_fd("command not found\n", 2);
	}
}

void	ft_pre_check_commands(t_cmds *list, t_env *n_envp)
{
	char	*path;
	char	**envp;

	check_exit_command(list);
	envp = ft_transform(n_envp);
	while (list)
	{
		path = ft_get_path(envp, list->str[0]);
		handle_command_not_found(path, list);
		if (path == NULL)
			return ;
		list = list->next;
	}
}
