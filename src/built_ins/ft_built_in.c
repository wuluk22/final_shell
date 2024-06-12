/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:33:11 by clegros           #+#    #+#             */
/*   Updated: 2024/06/01 15:23:07 by clegros          ###   ########.fr       */
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

void	launch_b(char **str, t_simple_cmds *cmd, char **env_p, t_env *envpp)
{
	if (str && ft_strncmp("echo", str[0], 4) == 0)
		ft_echo(cmd);
	else if (str && ft_strncmp("cd", str[0], 2) == 0)
		ft_cd(cmd);
	else if (str && ft_strncmp("pwd", str[0], 3) == 0)
		ft_pwd(cmd);
	else if (str && ft_strncmp("export", str[0], 6) == 0)
		ft_export(cmd, env_p, envpp);
	else if (str && ft_strncmp("unset", str[0], 5) == 0)
		ft_unset(cmd);
	else if (str && ft_strncmp("env", str[0], 3) == 0)
		ft_env(cmd, env_p, envpp);
	else if (str && ft_strncmp("exit", str[0], 4) == 0)
		ft_exit(cmd);
	else
		perror("bad");
}
