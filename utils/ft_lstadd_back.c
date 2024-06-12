/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:15:58 by clegros           #+#    #+#             */
/*   Updated: 2023/10/15 21:49:33 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

/*int main(void)
{
    t_list *my_list = NULL;

    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    ft_lstadd_back(&my_list, node1);
    ft_lstadd_back(&my_list, node2);
    ft_lstadd_back(&my_list, node3);

    t_list *current = my_list;
    while (current != NULL)
	{
        printf("%s\n", (char *)(current->content));
        current = current->next;
    }

    ft_lstclear(&my_list, free);

    return (0);
}*/