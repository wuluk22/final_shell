/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:03:20 by clegros           #+#    #+#             */
/*   Updated: 2023/10/11 19:55:10 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*int		main(void)
{
	char	buffer[10] = "abcdefghij";
	printf("Original buffer: %s\n", buffer);
	ft_bzero(buffer, 5);
	printf("Buffer after ft_bzero: %s\n", buffer);
	return (0);
}*/