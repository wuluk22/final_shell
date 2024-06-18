/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:49:59 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:27:22 by clegros          ###   ########.fr       */
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
	var_name = strndup(dollar_pos + 1, var_len);
	if (!var_name)
	{
		perror("strndup");
		exit(EXIT_FAILURE);
	}
	return (var_name);
}

static char	*ft_env_var_substitution(char *expanded_arg, char *dollar_pos)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	char	*next_char;

	next_char = dollar_pos + 1;
	var_name = ft_extract_env_var_name(dollar_pos);
	var_value = ft_get_env_value(var_name);
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

char	*ft_replace_env_variable(char *expanded_arg, char *dollar_pos)
{
	char	*temp;

	temp = ft_env_var_substitution(expanded_arg, dollar_pos);
//free(expanded_arg);
	return (temp);
}

int	ft_expander(t_cmds *cmd_list)
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
			expanded_str = ft_expand_variable(list->str[i]);
			if (!expanded_str)
			{
				//ft_putstr_fd("Error-$\n", STDERR_FILENO);
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

/*static char	*ft_expand_variable(const char *arg)
{
	char	*expanded_arg;
	char	*dollar_pos;
	char	*quote_pos;
	bool	single_quote;

	single_quote = false;
	expanded_arg = ft_strdup(arg);
	if (!expanded_arg)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	dollar_pos = ft_strchr(expanded_arg, '$');
	while (dollar_pos)
	{
		quote_pos = dollar_pos - 1;
		while (quote_pos >= expanded_arg && *quote_pos == '\'')
		{
			if (*quote_pos == '\'')
				single_quote = true;
			quote_pos--;
		}
		if (single_quote == false)
		{
			char	*replacement;
			if (*(dollar_pos + 1) == '?')
				replacement = ft_replace_exit_status(expanded_arg);
			else
				replacement = ft_replace_env_variable(expanded_arg, dollar_pos);
			if (!replacement)
			{
				free(expanded_arg);
				return (NULL);
			}
			expanded_arg = replacement;
		}
		dollar_pos = ft_strchr(dollar_pos + 1, '$');
	}
	return (expanded_arg);
}

char	*ft_replace_env_variable(char *expanded_arg, char *dollar_pos)
{
	char	*end_var;
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*temp;

	end_var = dollar_pos + 1;
	while (*end_var && (ft_isalnum(*end_var) || *end_var == '_'))
		end_var++;
	var_len = end_var - (dollar_pos + 1);
	var_name = strndup(dollar_pos + 1, var_len);
	if (!var_name)
	{
		perror("strndup");
		exit(EXIT_FAILURE);
	}
	var_value = ft_get_env_value(var_name);
	free(var_name);
	if (!var_value)
	{
		ft_putstr_fd("env var not found\n", STDERR_FILENO);
		return (NULL);
	}
	temp = ft_replace_substr(expanded_arg, dollar_pos, var_value);
	//free(expanded_arg);
	if (!temp)
	{
		perror("replace substr");
		free(var_value);
		exit(EXIT_FAILURE);
	}
	return (temp);
}*/