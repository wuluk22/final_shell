/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:08:09 by clegros           #+#    #+#             */
/*   Updated: 2023/10/10 14:35:17 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

/*#include <ctype.h>

int main(void)
{
	unsigned char num = 2;
	printf("%d\n", (ft_isdigit(num)));
	printf("%d\n", (isdigit(num)));
	return (0);
}*/
