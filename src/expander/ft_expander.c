/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:49:59 by clegros           #+#    #+#             */
/*   Updated: 2024/06/24 12:26:18 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace_exit_status(char *expanded_arg)
{
	char	*exit_status_str;
	char	*temp;

	exit_status_str = ft_itoa(g_exit_global);
	if (!exit_status_str)
	{
		perror("itoa fail");
		exit(EXIT_FAILURE);
	}
	temp = ft_replace_substr(expanded_arg, "$?", exit_status_str);
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

static char	*ft_extract_env_var_name(char *dollar_pos)
{
	char	*end_var;
	char	*var_name;
	int		var_len;

	end_var = dollar_pos + 1;
	while (*end_var && (ft_isalnum(*end_var) || *end_var == '_'))
		end_var++;
	var_len = end_var - (dollar_pos + 1);
	var_name = ft_strdup(dollar_pos + 1);
	if (!var_name)
	{
		perror("strndup");
		exit(EXIT_FAILURE);
	}
	return (var_name);
}

static char	*ft_var_sub(t_env **n_envp, char *expanded_arg, char *dollar_pos)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	char	*next_char;

	next_char = dollar_pos + 1;
	var_name = ft_extract_env_var_name(dollar_pos);
	var_value = ft_get_env_value(*n_envp, var_name);
	if (!var_value)
	{
		if (*next_char == '\0')
			ft_putchar_fd('$', STDOUT_FILENO);
		return (NULL);
	}
	free(var_name);
	temp = ft_replace_substr(expanded_arg, dollar_pos, var_value);
	if (!temp)
	{
		perror("replace substr");
		free(var_value);
		exit(EXIT_FAILURE);
	}
	return (temp);
}

char	*ft_rep_env_var(t_env **n_envp, char *expanded_arg, char *dollar_pos)
{
	char	*temp;

	temp = ft_var_sub(n_envp, expanded_arg, dollar_pos);
	return (temp);
}

int	ft_expander(t_cmds *cmd_list, t_env **n_envp)
{
	t_cmds	*list;
	int		i;
	char	*expanded_str;

	list = cmd_list;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			expanded_str = ft_expand_variable(n_envp, list->str[i]);
			if (!expanded_str)
			{
				list->str[i] = NULL;
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
