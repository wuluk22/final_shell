/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:09:26 by clegros           #+#    #+#             */
/*   Updated: 2023/10/14 23:20:02 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_limit(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (NULL);
}

static unsigned int	ft_count(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while ((n / 10) > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			count;
	char		*str;

	if (n == 0 || n == -2147483648)
		return (ft_limit(n));
	count = ft_count(n);
	str = malloc((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[count] = '\0';
	while (n != 0)
	{
		str[--count] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

/*int main(void)
{
    int test_values[] = {0, -2147483648, 42, -123456, 987654};
    int length = 5;
    int i = 0;

    while (i < length)
	{
        int n = test_values[i];
        char *result = ft_itoa(n);

        if (result == NULL)
		{
            printf("Memory allocation failed.\n");
            return (1);
        }

        printf("ft_itoa(%d) = %s\n", n, result);
        free(result);

        i++;
    }
    return (0);
}*/