/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:36:34 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 13:03:50 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	b;
	void	*p;

	b = count * size;
	p = malloc(b);
	if (p == NULL)
		return (NULL);
	else
		ft_bzero(p, b);
	return (p);
}

/*int main(void)
{
    size_t	num_elements = 5;
    size_t	element_size = sizeof(int);
	size_t	i = 0;

    int *int_array = (int *)ft_calloc(num_elements, element_size);

    if (int_array == NULL)
	{
        printf("Memory allocation failed.\n");
        return (1);
    }

    while (i < num_elements)
	{
        if (int_array[i] != 0)
		{
            printf("Memory not properly initialized.\n");
            free(int_array);
            return (1);
        }
		i++;
    }

    printf("Memory allocated and initialized successfully.\n");

    free(int_array);

    return (0);
}*/
