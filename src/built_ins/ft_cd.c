/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:33:23 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:22:53 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_update_pwd(t_env *envp)
{
	while (envp)
	{
		if (ft_strncmp(envp->key, "PWD", 3) == 0)
		{
			free(envp->value);
			envp->value = ft_strdup(getcwd(NULL, 0));
			return ;
		}
		envp = envp->next;
	}
}

static int	ft_change_directory(t_cmds *cmd, char **crt_wd, char **new_wd)
{
	*crt_wd = getcwd(NULL, 0);
	if (!(*crt_wd))
	{
		perror("getcwd");
		return (1);
	}
	*crt_wd = ft_strjoin(*crt_wd, "/");
	*new_wd = ft_strjoin(*crt_wd, cmd->str[1]);
	if (chdir(*new_wd) == -1 || cmd->str[2])
	{
		g_exit_global = 1;
		ft_putstr_fd("No such file or directory\n", 2);
		free(*crt_wd);
		free(*new_wd);
		return (1);
	}
	return (0);
}

static t_env	*ft_change_pwd(t_cmds *cmd, t_env **n_envp)
{
	t_env	*head;
	char	*crt_wd;
	char	*new_wd;

	head = *n_envp;
	if (ft_change_directory(cmd, &crt_wd, &new_wd) != 0)
		return (NULL);
	ft_update_pwd(head);
	free(crt_wd);
	free(new_wd);
	return (head);
}

/*static t_env	*ft_change_pwd(t_cmds *cmd, t_env **n_envp)
{
	t_env	*head;
	t_env	*current;
	char	*crt_wd;
	char	*new_wd;
	int		i;
	int		ret;

	i = 0;
	head = *n_envp;
	current = *n_envp;
	while (ft_strncmp(current->key, "PWD", 3) != 0)
		current = current->next;
	current->next->value = ft_strdup(getcwd(NULL, 0));

	crt_wd = getcwd(NULL, 0);
	if (!crt_wd)
	{
		perror("getcwd");
		return (NULL);
	}
	crt_wd = ft_strjoin(crt_wd, "/");
	new_wd = ft_strjoin(crt_wd, cmd->str[1]);
	if (chdir(new_wd) == -1 || cmd->str[2])
	{
		g_exit_global = 1;
		if (i == 0)
			ft_putstr_fd(" No such file or directory\n", 2);
		i++;
		free(crt_wd);
		free(new_wd);
		return (NULL);
	}
	ret = chdir(new_wd);
	current->value = ft_strdup(getcwd(NULL, 0));
	current = head;
	free(crt_wd);
	free(new_wd);
	return (current);
}*/

t_env	*ft_cd(t_cmds *cmd, t_env *n_envp)
{
	n_envp = ft_change_pwd(cmd, &n_envp);
	return (n_envp);
}
