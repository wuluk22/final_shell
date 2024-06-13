/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:48:28 by yohanafi          #+#    #+#             */
/*   Updated: 2024/06/05 15:24:45 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define TMP_FILE ".heredoc"

static char	*ltrim(char *str)
{
	while (isspace((unsigned char)*str))
		str++;
	return (str);
}

static char	*rtrim(char *str)
{
	char	*end;

	end = str + strlen(str) - 1;
	while (end >= str && isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

char	*trim(char *str)
{
	return (rtrim(ltrim(str)));
}

static void	exec(char **cmd, t_env *n_envp)
{
	char	*path;
	char	**envp;

	envp = ft_transform(n_envp);
	if (!*cmd || !cmd)
		return ;
	if (!cmd)
		exit(EXIT_FAILURE);
	path = get_path(*cmd, envp);
	if (!path)
		exit(EXIT_FAILURE);
	if (execve(path, cmd, envp) == -1)
		exit(EXIT_FAILURE);
}

static void	ft_close(int *fd)
{
	close(*fd);
	*fd = -1;
}

void	open_file(int fd, t_simple_cmds *cmd, int sv_stdin, int nb)
{
	if (nb == 0)
		fd = open(trim(cmd->redirections->next->token), O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (nb == 1)
		fd = open(trim(cmd->redirections->next->token), O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (nb == 2)
		fd = open(trim(cmd->redirections->next->token), O_RDONLY, 0777);
	if (nb == 3)
	{
		fd = open("feuys.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777);
		dup2(sv_stdin, 0);
		here_txt(trim(cmd->redirections->next->token), cmd, fd);
		close(fd);
		fd = open("feuys.txt", O_RDONLY, 0777);
		dup2(fd, 0);
	}
	if (nb == 0 || nb == 1)
		dup2(fd, 1);
	if (nb == 2)
		dup2(fd, 0);
	close(fd);
}

static void	ft_check(t_simple_cmds *cmd, int fd, int sv_stdin)
{
	while (cmd->redirections->token != NULL)
	{
		if (!ft_strncmp(cmd->redirections->token, ">", 1) && ft_strlen(cmd->redirections->token) == 1)
			open_file(fd, cmd, sv_stdin, 0);
		if (!ft_strncmp(cmd->redirections->token, ">>", 2) && ft_strlen(cmd->redirections->token) == 2)
			open_file(fd, cmd, sv_stdin, 1);
		if (!ft_strncmp(cmd->redirections->token, "<", 1) && ft_strlen(cmd->redirections->token) == 1)
			open_file(fd, cmd, sv_stdin, 2);
		if (!ft_strncmp(cmd->redirections->token, "<<", 1) && ft_strlen(cmd->redirections->token) == 2)
			open_file(fd, cmd, sv_stdin, 3);
		if (cmd->redirections->next != NULL)
			cmd->redirections = cmd->redirections->next;
		else
			break ;
	}
}

static void	ft_proccess(t_simple_cmds *cmd, int nb, int argc, t_env *n_envp)
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
	if (check_built_ins(cmd->str) == 0)
	{
		cmd->builton = cmd->str[0];
	//b_exec(cmd->str, envp, cmd);
		//write(2, "jo\n", 3);
		launch_b(cmd->str, cmd, n_envp);
	}
	else if (check_built_ins(cmd->str) == 1)
		exec(cmd->str, n_envp);
	close(sv_stdin);
	//exec(cmd->str, env_p);
}

static pid_t	ft_pipe(t_simple_cmds *cmd, int nb, int argc, t_env *n_envp)
{
	pid_t	pid;

	if (!cmd)
		return (0);
	if (nb < argc)
		if (pipe(cmd->p_fd_output) == -1)
			exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		ft_proccess(cmd, nb, argc, n_envp);
		exit(EXIT_SUCCESS);
	}
	ft_close(&cmd->p_fd_input[0]);
	ft_close(&cmd->p_fd_output[1]);
	if (cmd->next)
		ft_memcpy(cmd->next->p_fd_input, cmd->p_fd_output,
				sizeof(cmd->p_fd_input));
	cmd->p_fd_output[0] = -1;
//cmd->p_fd_output[1] = -1;
	return (pid);
}

void	ft_multi_pipe(int argc, t_simple_cmds *list, t_env *n_envp)
{
	int		i;
	int		status;
	pid_t	*pid;

	i = -1;
	pid = malloc((argc + 1) * sizeof(pid_t));
	if (!pid || !list)
		return ;
	ft_memset(pid, 0, (argc + 1) * sizeof(pid_t));
	list->p_fd_input[0] = -1;
	list->p_fd_input[1] = -1;
	while (++i <= argc)
	{
		pid[i] = ft_pipe(list, i, argc, n_envp);
		if (list->next)
			list = list->next;
	}
	i = 0;
	while (pid[i])
		waitpid(pid[i++], &status, 0);
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_exit_global = WEXITSTATUS(status);
	free(pid);
}
