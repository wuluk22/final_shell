/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:33:23 by clegros           #+#    #+#             */
/*   Updated: 2024/07/02 15:55:04 by yohanafi         ###   ########.fr       */
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
	if (access(*new_wd, R_OK) == -1 || cmd->str[2])
	{
		printf("minishell: %s: %s: No such file or directory\n",
			cmd->str[0], cmd->str[1]);
		g_exit_global = 1;
		free(*crt_wd);
		free(*new_wd);
		return (1);
	}
	else
		chdir(*new_wd);
	return (0);
}

static t_env	*ft_change_pwd(t_cmds *cmd, t_env **n_envp)
{
	t_env	*head;
	t_env	*current;
	char	*crt_wd;
	char	*new_wd;
	char	*cd;

	head = *n_envp;
	current = head;
	crt_wd = NULL;
	new_wd = NULL;
	cd = NULL;
	if (cmd->str[1])
		if (ft_change_directory(cmd, &crt_wd, &new_wd) != 0)
			return (head);
	if (!cmd->str[1])
	{
		while (ft_strncmp(current->key, "HOME", 4) != 0)
			if (current->next != NULL)
				current = current->next;
		chdir(current->value);
	}
	ft_update_pwd(head);
	free(crt_wd);
	free(new_wd);
	return (head);
}

t_env	*ft_cd(t_cmds *cmd, t_env *n_envp)
{
	n_envp = ft_change_pwd(cmd, &n_envp);
	return (n_envp);
}
