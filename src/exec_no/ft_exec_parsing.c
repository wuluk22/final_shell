/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:07:25 by clegros           #+#    #+#             */
/*   Updated: 2024/05/29 12:57:47 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char **envp, t_pipex *pipex)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			flag = 1;
		i++;
	}
	if (flag == 0)
	{
		error();
		close(pipex->tube[0]);
		close(pipex->tube[1]);
		close(pipex->infile);
		close(pipex->outfile);
		exit(1);
	}
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

char	*parsing(char **cmd_paths, char *cmd_args)
{
	char	*temp;
	char	*cmd;

	while (*cmd_paths)
	{
		temp = ft_strjoin(*cmd_paths, "/");
		cmd = ft_strjoin(temp, cmd_args);
		free(temp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		cmd_paths++;
	}
	return (NULL);
}
