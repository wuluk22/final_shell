/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:33:11 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 15:58:40 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_built_ins(char **str)
{
	if (str && ft_strncmp("echo", str[0], 4) == 0)
		return (0);
	else if (str && ft_strncmp("cd", str[0], 2) == 0)
		return (0);
	else if (str && ft_strncmp("pwd", str[0], 3) == 0)
		return (0);
	else if (str && ft_strncmp("export", str[0], 6) == 0)
		return (0);
	else if (str && ft_strncmp("unset", str[0], 5) == 0)
		return (0);
	else if (str && ft_strncmp("env", str[0], 3) == 0)
		return (0);
	else if (str && ft_strncmp("exit", str[0], 4) == 0)
		return (0);
	else
		return (1);
}

void	launch_b(char **str, t_simple_cmds *cmd, t_env **n_envp)
{
	if (str && ft_strncmp("echo", str[0], 4) == 0)
		ft_echo(cmd);
	else if (str && ft_strncmp("cd", str[0], 2) == 0)
		*n_envp = ft_cd(cmd, *n_envp);
	else if (str && ft_strncmp("pwd", str[0], 3) == 0)
		ft_pwd(cmd);
	else if (str && ft_strncmp("export", str[0], 6) == 0)
		*n_envp = ft_export(cmd, *n_envp);
	else if (str && ft_strncmp("unset", str[0], 5) == 0)
		*n_envp = ft_unset(cmd, *n_envp);
	else if (str && ft_strncmp("env", str[0], 3) == 0)
		ft_env(cmd, *n_envp);
	else if (str && ft_strncmp("exit", str[0], 4) == 0)
		ft_exit(cmd);
	else
		perror("bad");
}
