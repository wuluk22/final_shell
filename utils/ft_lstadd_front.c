/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:32:04 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 12:57:54 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*int main(void)
{
    t_list *my_list = NULL;

    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    ft_lstadd_front(&my_list, node3);
    ft_lstadd_front(&my_list, node2);
    ft_lstadd_front(&my_list, node1);

    t_list *current = my_list;
    while (current != NULL)
	{
        printf("%s\n", (char *)(current->content));
        current = current->next;
    }

    ft_lstclear(&my_list, free);
    return (0);
}*/
