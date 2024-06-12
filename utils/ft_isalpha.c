/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:06:56 by clegros           #+#    #+#             */
/*   Updated: 2023/10/11 15:40:12 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((65 <= c && c <= 90) || (97 <= c && c <= 122))
		return (1);
	return (0);
}

/*#include <ctype.h>
#include <stdio.h>

int main(void)
{
	unsigned char word = 'A';
	printf("%d\n", (ft_isalpha(word)));
	
	printf("%d\n", (isalpha(word)));
	return (0);
}*/
