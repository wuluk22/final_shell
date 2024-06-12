/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:26:14 by clegros           #+#    #+#             */
/*   Updated: 2023/10/14 14:33:12 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*void printCharIndex(unsigned int index, char *c)
{
    printf("Character at index %u: %c\n", index, *c);
}

int main(void)
{
    char str[] = "Hello, World!";

    ft_striteri(str, &printCharIndex);

    return (0);
}*/