/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:49:59 by clegros           #+#    #+#             */
/*   Updated: 2024/06/01 15:29:39 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_exit_status(char *expanded_arg)
{
	char	*exit_status_str;
	char	*temp;

	exit_status_str = ft_itoa(g_exit_global);
	if (!exit_status_str)
	{
		perror("itoa fail");
		exit(EXIT_FAILURE);
	}
	temp = replace_substr(expanded_arg, "$?", exit_status_str);
	free(expanded_arg);
	if (!temp)
	{
		perror("temp error");
		free(exit_status_str);
		exit(EXIT_FAILURE);
	}
	free(exit_status_str);
	return (temp);
}

static char	*replace_env_variable(char *expanded_arg, char *dollar_pos)
{
	char	*end_var;
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*temp;

	end_var = dollar_pos + 1;
	while (*end_var && (isalnum(*end_var) || *end_var == '_'))
		end_var++;
	var_len = end_var - (dollar_pos + 1);
	var_name = strndup(dollar_pos + 1, var_len);
	if (!var_name)
	{
		perror("strndup");
		exit(EXIT_FAILURE);
	}
	var_value = get_env_value(var_name);
	free(var_name);
	if (!var_value)
	{
		ft_putstr_fd("env var not found\n", STDERR_FILENO);
		return (NULL);
	}
	temp = replace_substr(expanded_arg, dollar_pos, var_value);
	free(expanded_arg);
	if (!temp)
	{
		perror("replace substr");
		free(var_value);
		exit(EXIT_FAILURE);
	}
	return (temp);
}

static char	*expand_variable(const char *arg)
{
	char	*expanded_arg;
	char	*dollar_pos;

	expanded_arg = strdup(arg);
	if (!expanded_arg)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	dollar_pos = strchr(expanded_arg, '$');
	while (dollar_pos)
	{
		if (*(dollar_pos + 1) == '?')
			expanded_arg = replace_exit_status(expanded_arg);
		else
			expanded_arg = replace_env_variable(expanded_arg, dollar_pos);
		if (!expanded_arg)
		{
			write(2, "Error-$\n", 8);
			break ;
		}
		dollar_pos = strchr(expanded_arg, '$');
	}
	return (expanded_arg);
}

int	expander(t_simple_cmds *cmd_list)
{
	t_simple_cmds	*list;
	int				i;
	char			*expanded_str;

	list = cmd_list;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			expanded_str = expand_variable(list->str[i]);
			if (!expanded_str)
			{
				ft_putstr_fd("Error-$\n", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			free(list->str[i]);
			list->str[i] = expanded_str;
			i++;
		}
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
