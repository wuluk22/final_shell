/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:07:58 by clegros           #+#    #+#             */
/*   Updated: 2024/05/31 13:08:01 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirect_token(t_lexer **tokens, t_lexer **redirections,
		t_lexer **current, t_lexer **prev)
{
	t_lexer	*next_token;

	next_token = (*current)->next;
	if (*prev == NULL)
		*tokens = next_token;
	else
		(*prev)->next = next_token;
	(*current)->next = *redirections;
	*redirections = *current;
	*current = next_token;
	if (*current != NULL)
	{
		next_token = (*current)->next;
		if (*prev == NULL)
			*tokens = next_token;
		else
			(*prev)->next = next_token;
		(*current)->next = *redirections;
		*redirections = *current;
		*current = next_token;
	}
}

void	parse_redirect_tokens(t_lexer **tokens, t_lexer **redirections)
{
	t_lexer	*current;
	t_lexer	*prev;

	current = *tokens;
	prev = NULL;
	while (current != NULL && ft_strncmp(current->token, "|", 1) != 0)
	{
		ft_strtrim(current->token, " ");
		if (is_redirection_token(current->token) == 0)
			handle_redirect_token(tokens, redirections, &current, &prev);
		else if (is_redirection_token(current->token) == 1)
			handle_redirect_token(tokens, redirections, &current, &prev);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	parse_redirections(t_lexer **tokens, t_lexer **redirections)
{
	parse_redirect_tokens(tokens, redirections);
	reverse_redirections_list(redirections);
}
