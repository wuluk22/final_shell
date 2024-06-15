/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:02:37 by clegros           #+#    #+#             */
/*   Updated: 2024/05/14 16:04:56 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_dbl_greater(t_lexer **list, char **t_start, char **crt)
{
	if (*crt != *t_start)
		ft_add_crt_token(list, t_start, *crt - 1);
	ft_add_token(list, ">>");
	*crt += 2;
	*t_start = *crt;
}

void	ft_handle_dbl_less(t_lexer **list, char **t_start, char **current)
{
	if (*current != *t_start)
		ft_add_crt_token(list, t_start, *current - 1);
	ft_add_token(list, "<<");
	*current += 2;
	*t_start = *current;
}

void	ft_handle_greater(t_lexer **list, char **token_start, char **current)
{
	if (*current != *token_start)
		ft_add_crt_token(list, token_start, *current - 1);
	ft_add_token(list, ">");
	(*current)++;
	*token_start = *current;
}

void	ft_handle_less(t_lexer **list, char **t_start, char **current)
{
	if (*current != *t_start)
		ft_add_crt_token(list, t_start, *current - 1);
	ft_add_token(list, "<");
	(*current)++;
	*t_start = *current;
}

void	ft_handle_pipe(t_lexer **list, char **t_start, char **current)
{
	if (*current != *t_start)
		ft_add_crt_token(list, t_start, *current - 1);
	ft_add_token(list, "|");
	(*current)++;
	*t_start = *current;
}
