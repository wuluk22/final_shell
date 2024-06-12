/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:09:22 by clegros           #+#    #+#             */
/*   Updated: 2023/10/17 11:33:07 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	void	*mapped_content;

	new_lst = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		mapped_content = f(lst->content);
		node = ft_lstnew(mapped_content);
		if (!node)
		{
			del(mapped_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}

/*void *map_function(void *content) {
    char *mapped_content = ft_strjoin("Mapped: ", (char *)content);
    return ((void *)mapped_content);
}

int main(void)
{
    t_list *my_list = ft_lstnew("Node 1");
    ft_lstadd_back(&my_list, ft_lstnew("Node 2"));
    ft_lstadd_back(&my_list, ft_lstnew("Node 3"));

    t_list *new_list = ft_lstmap(my_list, map_function, free);

    printf("Mapped list:\n");
    t_list *current = new_list;
    while (current != NULL)
	{
        printf("%s\n", (char *)(current->content));
        current = current->next;
    }

    ft_lstclear(&my_list, free);
    ft_lstclear(&new_list, free);
    return (0);
}*/