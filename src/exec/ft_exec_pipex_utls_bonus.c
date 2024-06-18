/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipex_utls_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:11:34 by yohanafi          #+#    #+#             */
/*   Updated: 2024/06/18 16:39:02 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_here_txt(t_cmds *cmd, char *limiter, int fd)
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
	unlink(".feuys.txt");
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

/*char	*ft_get_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path_cmd;
	char	*full_paths;
	int		i;

	i = 0;
	if (!access(cmd, X_OK))
	{
		return (cmd);
	}
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i++], "/");
		full_paths = ft_strjoin(path_cmd, ft_strtrim(cmd, " "));
		if (!path_cmd)
			free(path_cmd);
		if (!access(full_paths, F_OK))
			return (full_paths);
		if (full_paths)
			free(full_paths);
	}
	return (ft_free_tab(paths));
}*/

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
