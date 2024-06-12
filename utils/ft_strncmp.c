/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:55:40 by clegros           #+#    #+#             */
/*   Updated: 2024/05/29 10:32:30 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0') && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int		main(void)
{
	char s1[] = "ABBA";
	char s2[] = "ABW";
	int	n = 3;
	int	result1 = ft_strncmp(s1, s2, n);
	int result2 = strncmp(s1, s2, n);

	printf("%d\n", result1);
	printf("%d\n", result2);

	return (0);
}*/
