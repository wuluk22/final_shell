/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:05:23 by clegros           #+#    #+#             */
/*   Updated: 2024/05/31 13:05:21 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_tokens(t_lexer *tokens)
{
	int		count;
	t_lexer	*temp;

	count = 0;
	temp = tokens;
	while (temp != NULL && ft_strncmp(temp->token, "|", 1) != 0)
	{
		if (!ft_meta(temp->token)) // Assuming ft_is_redirection checks if token is a redirection
			count++;
		temp = temp->next;
	}
	return (count);
}

static void	ft_fill_command_strings(t_lexer **tokens, t_cmds *new_cmd)
{
	t_lexer	*current;
	char	*trimmed;
	int		i;

	current = *tokens;
	i = 0;
	while (current != NULL && ft_strncmp(current->token, "|", 1) != 0)
	{
		if (!ft_meta(current->token))
		{
			trimmed = ft_strtrim(current->token, " ");
			if (ft_strncmp(trimmed, "\"", 1) == 0)
				trimmed = ft_strtrim(trimmed, "\"");
			free(current->token);
			current->token = trimmed;
			new_cmd->str[i++] = ft_trim(current->token);
		}
		current = current->next;
	}
	new_cmd->str[i] = NULL;
	*tokens = current;
}

static void	ft_malloc_ex(void)
{
	printf("Memory allocation error\n");
	exit(EXIT_FAILURE);
}

void	ft_parse_command(t_cmds **cmd_list, t_lexer **tokens)
{
	t_lexer	*current;
	t_lexer	*cmd_start;
	t_lexer	*redirections;
	t_cmds	*new_cmd;
	int		token_count;

	current = *tokens;
	cmd_start = current;
	redirections = NULL;
	new_cmd = ft_create_simple_cmd_node();
	ft_parse_redirections(&cmd_start, &redirections);

	token_count = ft_count_tokens(cmd_start);
	if (new_cmd->str != NULL)
		ft_free_array(new_cmd->str);
	new_cmd->str = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (new_cmd->str == NULL)
		ft_malloc_ex();
	ft_fill_command_strings(&cmd_start, new_cmd);
	new_cmd->redirections = redirections;
	ft_add_spl_cmd(cmd_list, new_cmd);
	if (cmd_start != NULL && ft_strncmp(cmd_start->token, "|", 1) == 0)
		*tokens = cmd_start->next;
	else
		*tokens = cmd_start;
}
