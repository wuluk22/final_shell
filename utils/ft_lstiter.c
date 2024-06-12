/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:08:30 by clegros           #+#    #+#             */
/*   Updated: 2023/10/15 22:08:49 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp != NULL)
	{
		(*f)(temp->content);
		temp = temp->next;
	}
}

/*void apply_function(void *content)
{
    printf("Applied function to element: %s\n", (char *)content);
}

int main(void)
{
    t_list *my_list = ft_lstnew("Node 1");
    ft_lstadd_back(&my_list, ft_lstnew("Node 2"));
    ft_lstadd_back(&my_list, ft_lstnew("Node 3"));

    printf("Before applying function:\n");
    t_list *current = my_list;
    while (current != NULL)
	{
        printf("%s\n", (char *)(current->content));
        current = current->next;
    }
    ft_lstiter(my_list, apply_function);
    return (0);
}*/