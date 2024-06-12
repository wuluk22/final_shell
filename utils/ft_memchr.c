/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:28:24 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 13:03:23 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

/*int main(void)
{
    char src[] = "This is a test string";
    int s_char = 'a';
    size_t search_len = strlen(source);
    void *res = ft_memchr(source, search_char, search_len);

    if (result != NULL)
        printf("Char '%c' found at pos %ld\n", s_char, (char *)res - src);
    else
        printf("Character not found in the string.\n");
    return (0);
}*/
