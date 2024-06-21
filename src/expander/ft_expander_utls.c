/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:48:57 by clegros           #+#    #+#             */
/*   Updated: 2024/06/21 15:21:56 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_ex_var(char *expanded_arg, char *dollar_pos, bool *single_quote)
{
	char	*quote_pos;

	quote_pos = dollar_pos - 1;
	while (quote_pos >= expanded_arg && *quote_pos == '\'')
	{
		if (*quote_pos == '\'')
			*single_quote = true;
		quote_pos--;
	}
	return (!*single_quote);
}

static char	*ft_expand_variable_main_loop(t_env **n_envp, char *expanded_arg, char *dollar_pos)
{
	bool	single_quote;
	char	*replacement;

	single_quote = false;
	while (dollar_pos)
	{
		if (ft_ex_var(expanded_arg, dollar_pos, &single_quote))
		{
			replacement = NULL;
			if (*(dollar_pos + 1) == '?')
				replacement = ft_replace_exit_status(expanded_arg);
			else
				replacement = ft_replace_env_variable(n_envp, expanded_arg, dollar_pos);
			if (!replacement)
			{
				free(expanded_arg);
				return (NULL);
			}
			//free(expanded_arg);
			expanded_arg = replacement;
		}
		dollar_pos = ft_strchr(dollar_pos + 1, '$');
	}
	return (expanded_arg);
}

char	*ft_expand_variable(t_env **n_envp, const char *arg)
{
	char	*expanded_arg;
	char	*dollar_pos;

	expanded_arg = ft_strdup(arg);
	if (!expanded_arg)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	dollar_pos = ft_strchr(expanded_arg, '$');
	return (ft_expand_variable_main_loop(n_envp, expanded_arg, dollar_pos));
}
