/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:54:28 by clegros           #+#    #+#             */
/*   Updated: 2023/10/14 14:25:14 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = 0;
	if (!s)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (res == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*char uppercase_char(unsigned int index, char c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 'A');
    else
        return (c);
}

int main(void)
{
    char str[] = "Hello, World!";

    char *result = ft_strmapi(str, &uppercase_char);

    if (result != NULL)
	{
        printf("Original: %s\n", str);
        printf("Modified : %s\n", result);

        free(result);
	}
    else
        printf("Memory allocation failed.\n");

    return (0);
}*/