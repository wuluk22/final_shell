/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:48:15 by clegros           #+#    #+#             */
/*   Updated: 2024/05/15 16:01:45 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer_to_cmds(t_cmds **cmd_list, t_lexer **tokens)
{
	while (*tokens != NULL)
		ft_parse_command(cmd_list, tokens);
}

void	ft_free_cmds(t_cmds *cmds)
{
	t_cmds	*temp;

	while (cmds != NULL)
	{
		temp = cmds;
		cmds = cmds->next;
		free(temp->str);
		ft_free_list(temp->redirections);
		free(temp);
	}
}
