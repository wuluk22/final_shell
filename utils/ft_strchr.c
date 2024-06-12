/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:21:49 by clegros           #+#    #+#             */
/*   Updated: 2023/10/14 20:13:27 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if ((unsigned char) c == '\0')
		return ((char *) s);
	return (NULL);
}

/*int main(void)
{
    const char str[] = "This is a test string.";
    int t_char = 'i';
    char *res = ft_strchr(str, targetChar);

    if (result != NULL)
        printf("'%c' found at pos: %lu\n", t_char, (unsigned long)(res - str));
    else
        printf("'%c' not found in the string.\n", t_char);

    return (0);
}*/