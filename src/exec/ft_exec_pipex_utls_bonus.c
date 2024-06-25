/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_utls_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:11:34 by yohanafi          #+#    #+#             */
/*   Updated: 2024/06/19 12:49:43 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_txt(t_cmds *cmd, char *limiter, int fd)
{
	char	*line;

	(void)cmd;
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(EXIT_FAILURE);
		if (!ft_strncmp(line, ft_trim(limiter), ft_strlen(ft_trim(limiter))))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
}

char	*ft_free_tab(char **tabs)
{
	size_t	i;

	i = 0;
	while (tabs[i])
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
	return (NULL);
}

void	ft_parent(t_cmds *cmd, pid_t pid)
{
	(void)pid;
	if (cmd->p_fd_input[0] != -1)
	{
		close(cmd->p_fd_input[0]);
		close(cmd->p_fd_input[1]);
	}
	if (cmd->next)
		ft_memcpy(cmd->next->p_fd_input, cmd->p_fd_output,
			sizeof(cmd->p_fd_input));
	cmd->p_fd_output[0] = -1;
	if (cmd->redirections)
		wait(NULL);
}

char	*ft_strnstr(const char *find, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!find && !len)
		return (0);
	if (to_find[0] == '\0' || to_find == find)
		return ((char *)find);
	while (find[i] != '\0')
	{
		j = 0;
		while (find[i + j] == to_find[j] && (i + j) < len)
		{
			if (find[i + j] == '\0' && to_find[j] == '\0')
				return ((char *)&find[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)(find + i));
		i++;
	}
	return (0);
}
