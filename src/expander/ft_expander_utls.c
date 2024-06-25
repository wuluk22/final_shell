/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:48:57 by clegros           #+#    #+#             */
/*   Updated: 2024/06/24 12:22:24 by clegros          ###   ########.fr       */
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

static char	*ft_exp_var_loop(t_env **n_envp, char *exp_arg, char *dollar_pos)
{
	bool	single_quote;
	char	*repl;

	single_quote = false;
	while (dollar_pos)
	{
		if (ft_ex_var(exp_arg, dollar_pos, &single_quote))
		{
			repl = NULL;
			if (*(dollar_pos + 1) == '?')
				repl = ft_replace_exit_status(exp_arg);
			else if (*(dollar_pos + 1) == '\0')  // Case for string that is only a dollar sign
				return exp_arg;
			else
				repl = ft_rep_env_var(n_envp, exp_arg, dollar_pos);
			if (!repl)
			{
				free(exp_arg);
				return (NULL);
			}
			//if (exp_arg)
			//	free(exp_arg);
			exp_arg = repl;
			dollar_pos = ft_strchr(exp_arg, '$');  // Reset dollar_pos to handle new expanded string
		}
		else
		{
			dollar_pos = ft_strchr(dollar_pos + 1, '$');
		}
	}
	return (exp_arg);
}

char	*ft_expand_variable(t_env **n_envp, const char *arg)
{
	char	*expanded_arg;
	char	*dollar_pos;

	if (ft_strncmp(arg, "$", ft_strlen(arg)) == 0)
		return (ft_strdup("$"));
	expanded_arg = ft_strdup(arg);
	if (!expanded_arg)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	dollar_pos = ft_strchr(expanded_arg, '$');
	return (ft_exp_var_loop(n_envp, expanded_arg, dollar_pos));
}
