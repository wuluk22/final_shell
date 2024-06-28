/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:06:30 by clegros           #+#    #+#             */
/*   Updated: 2024/06/28 11:35:38 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	ft_init_multi(t_cmds *list)
{
	list->p_fd_input[0] = -1;
	list->p_fd_input[1] = -1;
}

void	ft_child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}

void	ft_waitpid(pid_t *pid, int argc, int status, int last_exit)
{
	int	j;

	j = 0;
	while (j < argc + 1)
	{
		waitpid(pid[j++], &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != 0)
				last_exit = WEXITSTATUS(status);
		if (last_exit != 0)
			g_exit_global = last_exit;
		if (last_exit == 0)
			g_exit_global = 0;
	}
}
