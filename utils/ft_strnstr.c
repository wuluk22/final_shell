/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:23:10 by clegros           #+#    #+#             */
/*   Updated: 2023/10/14 20:24:35 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *find, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
	{
		return ((char *)find);
	}
	while (find[i] != '\0' && to_find[j] != '\0' && i < len)
	{
		if (find[i] == to_find[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (to_find[j] == '\0')
		return ((char *)&find[i - j]);
	return (NULL);
}

/*int main(void)
{
    const char haystack[] = "This is a test string.";
    const char needle[] = "test";

    char *result = ft_strnstr(haystack, needle, sizeof(haystack));

    if (result != NULL)
        printf("Needle found at position: %zu\n", result - haystack);
    else
        printf("Needle not found.\n");

    return (0);
}*/