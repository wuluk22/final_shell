/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:56:50 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 13:15:30 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_list(t_lexer *list)
{
	t_lexer	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->token);
		free(temp);
	}
}

void	ft_print_list(t_lexer *list)
{
	int	i;

	i = 1;
	while (list != NULL)
	{
		printf("lexer %d : %s\n", i++, list->token);
		list = list->next;
	}
}

void	ft_add_token(t_lexer **list, t_lexer *new_token, const char *token)
{
	t_lexer	*current;
	char	*trimmed_token;

	trimmed_token = ft_strtrim(token, " ");
	new_token->token = ft_strdup(trimmed_token);
	if (new_token == NULL || trimmed_token == NULL || new_token->token == NULL)
	{
		free(trimmed_token);
		free(new_token);
		printf("Erreur d'allocation mémoire\n");
		exit(EXIT_FAILURE);
	}
	free(trimmed_token);
	new_token->next = NULL;
	if (*list == NULL)
		*list = new_token;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

void	ft_add_crt_token(t_lexer **list, char **tok_start, char *current)
{
	t_lexer	*new_token;
	char	*trimmed;

	new_token = NULL;
	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return ;
	*current = '\0';
	trimmed = ft_strtrim(*tok_start, " ");
	if (trimmed == NULL)
	{
		exit(EXIT_FAILURE);
	}
	ft_add_token(list, new_token, trimmed);
	free(trimmed);
	*tok_start = current + 1;
}
