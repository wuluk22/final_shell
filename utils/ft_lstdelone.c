/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:56:02 by clegros           #+#    #+#             */
/*   Updated: 2023/10/15 22:15:22 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*int main(void)
{
    t_list *my_list = ft_lstnew("Node 1");

    printf("Before deletion:\n");
    printf("%s\n", (char *)(my_list->content));

    ft_lstdelone(my_list, free);

    printf("After deletion:\n");
    if (my_list == NULL)
        printf("List is empty.\n");
    return (0);
}*/