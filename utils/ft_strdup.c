/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:59:48 by clegros           #+#    #+#             */
/*   Updated: 2023/10/19 13:54:06 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		size_c;

	size_c = ft_strlen(s1) + 1;
	copy = (char *) malloc(sizeof(char) * (size_c));
	if (copy == NULL)
		return (NULL);
	ft_strcpy(copy, (char *)s1);
	return (copy);
}

/*int	main(void)
{
	char	s[] = "Hello Wurld";
	char	*dup = ft_strdup(s);
	
	if (dup != NULL)
	{
		printf("%s", dup);
		free(dup);
	}
	return (0);
}*/
