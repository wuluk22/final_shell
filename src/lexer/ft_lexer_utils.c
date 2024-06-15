/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:56:50 by clegros           #+#    #+#             */
/*   Updated: 2024/05/14 16:02:05 by clegros          ###   ########.fr       */
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
	free(list);
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

void	ft_add_token(t_lexer **list, char *token)
{
	t_lexer	*new_token;
	t_lexer	*current;
	char	*trimmed_token;

	trimmed_token = ft_strtrim(token, " ");
	if (trimmed_token == NULL)
	{
		fprintf(stderr, "Erreur d'allocation mémoire\n");
		exit(EXIT_FAILURE);	
	}
	new_token = malloc(sizeof(t_lexer));
	if (new_token == NULL)
	{
		free(trimmed_token);
		fprintf(stderr, "Erreur d'allocation mémoire\n");
		exit(EXIT_FAILURE);
	}
	new_token->token = NULL;
	new_token->token = strdup(trimmed_token);
	free(trimmed_token);
	if (new_token->token == NULL)
	{
		//free(new_token->token);
		free(new_token);
		exit(EXIT_FAILURE);
	}
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
	//new_token->token = NULL;
}

void	ft_add_crt_token(t_lexer **list, char **tok_start, char *current)
{
	*current = '\0';
	ft_strtrim(*tok_start, " ");
	ft_add_token(list, *tok_start);
	*tok_start = current + 1;
}
