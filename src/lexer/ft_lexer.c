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

void	ft_handle_quotes(char crt_char, char *crt_quote, bool *in_quotes)
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

void	ft_hdl_m(t_lexer **list, char **t_start, char **crt, bool *in_qts)
{
	if (!*in_qts)
	{
		if (ft_strncmp(*crt, "<<", 2) == 0)
			ft_handle_dbl_less(list, t_start, crt);
		else if (ft_strncmp(*crt, ">>", 2) == 0)
			ft_handle_dbl_greater(list, t_start, crt);
		else if (**crt == '<')
			ft_handle_less(list, t_start, crt);
		else if (**crt == '>')
			ft_handle_greater(list, t_start, crt);
		else if (**crt == '|')
			ft_handle_pipe(list, t_start, crt);
	}
}

void	ft_tokenize(t_lexer **list, char *cmd)
{
	t_lexer	*new_token;
	char	*token_start;
	char	*current;
	char	current_quote;
	bool	in_quotes;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	token_start = cmd;
	current = cmd;
	current_quote = '\0';
	in_quotes = false;
	while (*current != '\0')
	{
		ft_handle_quotes(*current, &current_quote, &in_quotes);
		ft_hdl_m(list, &token_start, &current, &in_quotes);
		if (!in_quotes && *current == ' ' && current != token_start)
			ft_add_crt_token(list, &token_start, current);
		current++;
	}
	if (current != token_start)
		ft_add_token(list, new_token, token_start);
}
