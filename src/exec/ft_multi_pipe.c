/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:56:37 by yohanafi          #+#    #+#             */
/*   Updated: 2024/06/28 12:02:21 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	initialize_pids(pid_t **pid, int argc)
{
	*pid = malloc((argc + 1) * sizeof(pid_t));
	if (*pid)
		ft_memset(*pid, 0, (argc + 1) * sizeof(pid_t));
}

static void	wait_for_children(pid_t *pid, int argc, int *last_exit)
{
	int	status;
	int	j;

	status = 0;
	j = 0;
	while (j < argc + 1)
	{
		waitpid(pid[j++], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			*last_exit = WEXITSTATUS(status);
	}
}

static void	update_exit_status(int last_exit)
{
	if (last_exit != 0)
		g_exit_global = last_exit;
	else
		g_exit_global = 0;
}

void	ft_multi_pipe(t_cmds *list, t_env **n_envp, int argc, int j)
{
	pid_t	*pid;
	int		last_exit;

	last_exit = 0;
	initialize_pids(&pid, argc);
	ft_pre_check_commands(list, *n_envp);
	if (!pid || !list)
		return ;
	ft_init_multi(list);
	while (++j <= argc)
	{
		pid[j] = ft_pipe(list, n_envp, j, argc);
		if (list->next)
			list = list->next;
	}
	wait_for_children(pid, argc, &last_exit);
	update_exit_status(last_exit);
	ft_free_multi(pid, last_exit);
}
