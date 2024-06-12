/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:24:31 by clegros           #+#    #+#             */
/*   Updated: 2023/10/14 20:16:31 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		i--;
		if (s[i] == (unsigned char) c)
			return ((char *)(s + i));
	}
	if ((unsigned char) c == '\0')
		return ((char *) s + ft_strlen(s));
	return (NULL);
}

/*int main(void)
{
    const char str[] = "This is a test string.";
    int t_char = 'i';
    char *res = ft_strrchr(str, t_char);

    if (res != NULL)
        printf("Last occurrence of '%c' found at pos: %zu\n", t_char, res - str);
    else
        printf("'%c' not found in the string.\n", t_char);

    return (0);
}*/