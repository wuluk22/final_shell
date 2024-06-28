/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:48:28 by yohanafi          #+#    #+#             */
/*   Updated: 2024/06/28 12:01:23 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define TMP_FILE ".heredoc"

void	ft_exec(t_env *n_envp, char **cmd)
{
	char	*path;
	char	**envp;

	envp = ft_transform(n_envp);
	if (!*cmd || !cmd)
		exit(127);
	path = ft_get_path(envp, *cmd);
	if (!path)
	{
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		exit(EXIT_FAILURE);
	}
	g_exit_global = 0;
}

void	ft_handle_process(t_cmds *cmd, int nb, int argc)
{
	int	fd;
	int	sv_stdin;

	sv_stdin = dup(0);
	fd = 0;
	if (nb > 0)
	{
		dup2(cmd->p_fd_input[0], 0);
		close(cmd->p_fd_input[0]);
		close(cmd->p_fd_input[1]);
	}
	if (nb < argc)
	{
		dup2(cmd->p_fd_output[1], 1);
		close(cmd->p_fd_output[0]);
		close(cmd->p_fd_output[1]);
	}
	if (cmd->redirections)
		ft_check(cmd, fd, sv_stdin);
	close(sv_stdin);
}

pid_t	ft_pipe(t_cmds *cmd, t_env **n_envp, int nb, int argc)
{
	pid_t	pid;

	if (!cmd)
		return (0);
	if (nb < argc)
	{
		if (pipe(cmd->p_fd_output) == -1)
		{
			if (cmd->p_fd_input[0] != -1)
			{
				ft_close(&cmd->p_fd_input[0]);
				ft_close(&cmd->p_fd_input[1]);
			}
			exit(EXIT_FAILURE);
		}
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		ft_process(cmd, n_envp, nb, argc);
	else
		ft_parent(cmd, pid);
	return (pid);
}
