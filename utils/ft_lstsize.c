/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:34:40 by clegros           #+#    #+#             */
/*   Updated: 2023/10/15 16:54:30 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	if (!lst)
		return (0);
	current = lst;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

/*int main(void)
{
    t_list *my_list = ft_lstnew("Node 1");
    ft_lstadd_back(&my_list, ft_lstnew("Node 2"));
    ft_lstadd_back(&my_list, ft_lstnew("Node 3"));

    int size = ft_lstsize(my_list);
    printf("Size of the list: %d\n", size);

    ft_lstclear(&my_list, free);
    return (0);
}*/