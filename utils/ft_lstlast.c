/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:45:22 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 14:23:29 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

/*int main(void)
{
    t_list *my_list = ft_lstnew("Node 1");
    ft_lstadd_back(&my_list, ft_lstnew("Node 2"));
    ft_lstadd_back(&my_list, ft_lstnew("Node 3"));

    t_list *last_element = ft_lstlast(my_list);

    if (last_element != NULL)
        printf("Last element: %s\n", (char *)(last_element->content));
    else
        printf("List is empty.\n");

    ft_lstclear(&my_list, free);
    return (0);
}*/
