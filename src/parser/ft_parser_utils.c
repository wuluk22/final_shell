/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:48:25 by clegros           #+#    #+#             */
/*   Updated: 2024/05/15 16:41:35 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0
		|| ft_strncmp(command, "cd", 2) == 0)
		return (true);
	return (false);
}

int	ft_is_redirection_token(const char *token)
{
	if (ft_strncmp(token, "<", 1) == 0 || ft_strncmp(token, ">", 1) == 0
		|| ft_strncmp(token, ">>", 2) == 0)
		return (0);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (1);
	else
		return (2);
}

void	ft_reverse_redirections_list(t_lexer **redirections)
{
	t_lexer	*prev_redir;
	t_lexer	*temp;

	prev_redir = NULL;
	temp = *redirections;
	while (*redirections != NULL)
	{
		temp = *redirections;
		*redirections = (*redirections)->next;
		temp->next = prev_redir;
		prev_redir = temp;
	}
	*redirections = prev_redir;
}

t_cmds	*ft_create_simple_cmd_node(void)
{
	t_cmds	*new_node;

	new_node = malloc(sizeof(t_cmds));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	new_node->str = NULL;
	new_node->num_redirections = 0;
	new_node->pid = 6;
	new_node->hd_file_name = NULL;
	new_node->redirections = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_add_spl_cmd(t_cmds **cmd_list, t_cmds *new_node)
{
	t_cmds	*current;

	if (*cmd_list == NULL)
		*cmd_list = new_node;
	else
	{
		current = *cmd_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}
