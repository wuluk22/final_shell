/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:48:28 by yohanafi          #+#    #+#             */
/*   Updated: 2024/06/18 16:37:36 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define TMP_FILE ".heredoc"

static void	ft_exec(t_env *n_envp, char **cmd)
{
	char	*path;
	char	**envp;

	envp = ft_transform(n_envp);
	if (!*cmd || !cmd)
		return ;
	if (!cmd)
		exit(EXIT_FAILURE);
	path = ft_get_path(envp, *cmd);
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

static void	ft_handle_process(t_cmds *cmd, int nb, int argc)
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

void	ft_process(t_cmds *cmd, t_env **n_envp, int nb, int argc)
{
	ft_handle_process(cmd, nb, argc);
	if (ft_check_built_ins(cmd->str) == 0)
	{
		cmd->builton = cmd->str[0];
		ft_launch_b(cmd, n_envp, cmd->str);
	}
	else if (ft_check_built_ins(cmd->str) == 1)
		ft_exec(*n_envp, cmd->str);
	exit(EXIT_SUCCESS);
}

static pid_t	ft_pipe(t_cmds *cmd, t_env **n_envp, int nb, int argc)
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

void	ft_multi_pipe(t_cmds *list, t_env **n_envp, int argc)
{
	pid_t	*pid;
	int		i;
	int		status;

	status = 0;
	i = -1;
	pid = malloc((argc + 1) * sizeof(pid_t));
	if (!pid || !list)
		return ;
	ft_memset(pid, 0, (argc + 1) * sizeof(pid_t));
	list->p_fd_input[0] = -1;
	list->p_fd_input[1] = -1;
	while (++i <= argc)
	{
		pid[i] = ft_pipe(list, n_envp, i, argc);
		if (list->next)
			list = list->next;
	}
	i = 0;
	while (i < argc + 1)
		waitpid(pid[i++], &status, 0);
	if (WIFEXITED(status))
		g_exit_global = WEXITSTATUS(status);
	free(pid);
}

/*static void	ft_proccess(t_cmds *cmd, t_env **n_envp, int nb, int argc)
{
	int	fd;
	int	sv_stdin;

	sv_stdin = dup(0);
	fd = 0;
	if (nb > 0)
	{
		dup2(cmd->p_fd_input[0], 0);
		close(cmd->p_fd_input[0]);
	}
	if (nb < argc)
	{
		dup2(cmd->p_fd_output[1], 1);
		close(cmd->p_fd_output[0]);
		close(cmd->p_fd_output[1]);
	}
	if (cmd->redirections)
		ft_check(cmd, fd, sv_stdin);
	if (ft_check_built_ins(cmd->str) == 0)
	{
		cmd->builton = cmd->str[0];
		ft_launch_b(cmd, n_envp, cmd->str);
	}
	else if (ft_check_built_ins(cmd->str) == 1)
		ft_exec(*n_envp, cmd->str);
	close(sv_stdin);
}*/
