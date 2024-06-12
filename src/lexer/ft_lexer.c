/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:52:14 by clegros           #+#    #+#             */
/*   Updated: 2024/05/14 15:56:39 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quotes(char crt_char, bool *in_quotes, char *crt_quote)
{
	if (crt_char == DOUBLE_QUOTE || crt_char == SINGLE_QUOTE)
	{
		if (*in_quotes && crt_char == *crt_quote)
		{
			*in_quotes = false;
			*crt_quote = '\0';
		}
		else if (!*in_quotes)
		{
			*in_quotes = true;
			*crt_quote = crt_char;
		}
	}
}

void	hdl_m(t_lexer **list, char **t_start, char **crt, bool *in_qts)
{
	if (!*in_qts)
	{
		if (strncmp(*crt, "<<", 2) == 0)
			handle_dbl_less(list, t_start, crt);
		else if (strncmp(*crt, ">>", 2) == 0)
			handle_dbl_greater(list, t_start, crt);
		else if (**crt == '<')
			handle_less(list, t_start, crt);
		else if (**crt == '>')
			handle_greater(list, t_start, crt);
		else if (**crt == '|')
			handle_pipe(list, t_start, crt);
	}
}

void	tokenize(char *cmd, t_lexer **list)
{
	char	*token_start;
	char	*current;
	bool	in_quotes;
	char	current_quote;

	token_start = cmd;
	current = cmd;
	in_quotes = false;
	current_quote = '\0';
	while (*current != '\0')
	{
		handle_quotes(*current, &in_quotes, &current_quote);
		hdl_m(list, &token_start, &current, &in_quotes);
		if (!in_quotes && *current == ' ' && current != token_start)
			add_crt_token(list, &token_start, current);
		current++;
	}
	if (current != token_start)
		add_token(list, token_start);
}
