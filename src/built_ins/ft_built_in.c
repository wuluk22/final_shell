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

static int	ft_exit_help(t_cmds *cmd_list, t_lexer *lexer_list)
{
	if (ft_exit(cmd_list) != 1)
	{
		ft_cleanup_cmd_list(cmd_list);
		ft_free_list(lexer_list);
		return (1);
	}
	return (0);
}

int	ft_b_ins(t_cmds *cmd_list, t_lexer *lexer_list, t_env **n_envp)
{
	if (cmd_list && cmd_list->str)
	{
		if (ft_strncmp(cmd_list->str[0], "exit", 4) == 0)
			if (ft_exit_help(cmd_list, lexer_list) == 1)
				return (1);
		if (ft_strncmp(cmd_list->str[0], "export", 6) == 0)
		{
			*n_envp = ft_export(cmd_list, *n_envp);
			return (0);
		}
		else if (ft_strncmp(cmd_list->str[0], "unset", 5) == 0)
		{
			*n_envp = ft_unset(cmd_list, *n_envp);
			return (0);
		}
		else if (ft_strncmp(cmd_list->str[0], "cd", 2) == 0)
		{
			*n_envp = ft_cd(cmd_list, *n_envp);
			return (0);
		}
		else
			ft_command_exec(cmd_list, n_envp, cmd_list->str);
	}
	return (0);
}

int	ft_check_built_ins(char **str)
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

void	ft_launch_b(t_cmds *cmd, t_env **n_envp, char **str)
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
