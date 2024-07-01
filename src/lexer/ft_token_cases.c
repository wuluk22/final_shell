/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:02:37 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 13:05:44 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_dbl_greater(t_lexer **list, char **t_start, char **crt)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return ;
	if (*crt != *t_start)
		ft_add_crt_token(list, t_start, *crt - 1);
	ft_add_token(list, new_token, ">>");
	*crt += 2;
	*t_start = *crt;
}

void	ft_handle_dbl_less(t_lexer **list, char **t_start, char **current)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return ;
	if (*current != *t_start)
		ft_add_crt_token(list, t_start, *current - 1);
	ft_add_token(list, new_token, "<<");
	*current += 2;
	*t_start = *current;
}

void	ft_handle_greater(t_lexer **list, char **token_start, char **current)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return ;
	if (*current != *token_start)
		ft_add_crt_token(list, token_start, *current - 1);
	ft_add_token(list, new_token, ">");
	(*current)++;
	*token_start = *current;
}

void	ft_handle_less(t_lexer **list, char **t_start, char **current)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return ;
	if (*current != *t_start)
		ft_add_crt_token(list, t_start, *current - 1);
	ft_add_token(list, new_token, "<");
	(*current)++;
	*t_start = *current;
}

void	ft_handle_pipe(t_lexer **list, char **t_start, char **current)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return ;
	if (*current != *t_start)
		ft_add_crt_token(list, t_start, *current - 1);
	ft_add_token(list, new_token, "|");
	(*current)++;
	*t_start = *current;
}
