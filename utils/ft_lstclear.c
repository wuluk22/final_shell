/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:03:56 by clegros           #+#    #+#             */
/*   Updated: 2023/10/15 22:04:26 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}

/*int main(void)
{
    t_list *my_list = ft_lstnew("Node 1");
    ft_lstadd_back(&my_list, ft_lstnew("Node 2"));
    ft_lstadd_back(&my_list, ft_lstnew("Node 3"));

    printf("Before clearing:\n");
    t_list *current = my_list;
    while (current != NULL)
	{
        printf("%s\n", (char *)(current->content));
        current = current->next;
    }

    ft_lstclear(&my_list, free);

    printf("After clearing:\n");
    current = my_list;
    if (current == NULL) {
        printf("List is empty.\n");
    }
    return (0);
}*/