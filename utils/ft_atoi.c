/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:53:55 by clegros           #+#    #+#             */
/*   Updated: 2024/05/14 16:05:56 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	ft_safe(long long int res, long long int temp, int sign)
{
	if (temp > res && sign == -1)
		return (0);
	else if (temp > res && sign == 1)
		return (-1);
	return (res);
}

int	ft_atoi(const char *str)
{
	long long int	res;
	int				sign;
	int				i;
	long long int	temp;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = res;
		res = res * 10 + (str[i] - '0');
		i++;
		res = ft_safe(res, temp, sign);
	}
	return (sign * res);
}

/*int	main(int argc, char *argv[])
{

	printf("%d\n", ft_atoi(argv[1]));
	printf("%d\n", atoi(argv[1]));
	return (0);
}*/
