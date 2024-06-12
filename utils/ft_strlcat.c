/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:55:13 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 13:44:01 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dst[i] && i < dstsize)
		i++;
	while (src[j] && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i != dstsize)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

/*int main(void)
{
    char s[] = "Hello";
    char d[11] = "julo";

    printf("%u\n", ft_strlcat(d, s, 8));
    printf("%s\n\n", d);

	char s1[] = "Hello";
	char d1[11] = "julo";

    printf("%lu\n", strlcat(d1, s1, 8));
    printf("%s\n\n", d1);
	ft_strlcat(0, 0, 5);
	strlcat(0, "d", 0);
    return 0;
}*/