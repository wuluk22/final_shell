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

void	lexer_to_cmds(t_lexer **tokens, t_simple_cmds **cmd_list)
{
	while (*tokens != NULL)
		parse_command(tokens, cmd_list);
}

void	free_cmds(t_simple_cmds *cmds)
{
	t_simple_cmds	*temp;

	while (cmds != NULL)
	{
		temp = cmds;
		cmds = cmds->next;
		free(temp->str);
		free_list(temp->redirections);
		free(temp);
	}
}
