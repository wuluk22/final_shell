/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_utls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:40:48 by clegros           #+#    #+#             */
/*   Updated: 2024/06/15 11:40:49 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_check_direct_access(char *cmd)
{
	if (!access(cmd, X_OK))
		return (cmd);
	return (NULL);
}

static char	*ft_find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*ft_get_path_from_paths(char **paths, char *cmd, char *path_cmd)
{
	char	*full_paths;
	int		i;

	full_paths = NULL;
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		if (!path_cmd)
			break ;
		full_paths = ft_strjoin(path_cmd, ft_strtrim(cmd, " "));
		free(path_cmd);
		if (!full_paths)
			break ;
		if (!access(full_paths, F_OK))
		{
			ft_free_tab(paths);
			return (full_paths);
		}
		free(full_paths);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

char	*ft_get_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*path_cmd;
	char	*direct_access;

	paths = NULL;
	path_env = NULL;
	path_cmd = NULL;
	direct_access = ft_check_direct_access(cmd);
	if (direct_access)
		return (direct_access);
	path_env = ft_find_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (ft_get_path_from_paths(paths, cmd, path_cmd));
}
