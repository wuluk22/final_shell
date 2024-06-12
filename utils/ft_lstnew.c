/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:24:41 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 14:27:30 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*int main(void)
{
    char *content = "Test Content";
    t_list *new_node = ft_lstnew(content);

    if (new_node != NULL)
	{
        printf("New node content: %s\n", (char *)(new_node->content));
        printf("New node next: %p\n", (void *)(new_node->next));
    }
    else
        printf("Memory allocation failed.\n");
    if (new_node != NULL)
        free(new_node);
    return (0);
}*/
