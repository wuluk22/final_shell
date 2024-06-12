/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:26:14 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 13:36:29 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	s = (char *)b;
	while (len > 0)
	{
		s[len - 1] = c;
		len--;
	}
	return (b);
}

/*int main(void)
{
    char buffer[20];

    size_t buffer_size = sizeof(buffer);
    ft_memset(buffer, 65, buffer_size);

    printf("Buffer after memset: %s\n", buffer);

    int isFilled = 1;
    size_t i = 0;
    while (i < buffer_size)
	{
        if (buffer[i] != 'A')
		{
            isFilled = 0;
            break;
        }
        i++;
    }

    if (isFilled)
        printf("Buffer has been correctly filled with 'A'.\n");
    else
        printf("Buffer has not been correctly filled.\n");

    return (0);
}*/
