/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:43:52 by clegros           #+#    #+#             */
/*   Updated: 2023/10/17 11:19:25 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_countwords(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += ft_wordlen(s, c);
		}
		else
			s++;
	}
	return (count);
}

static void	*ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	count = ft_countwords(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	strs[count] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			strs[i] = ft_substr(s, 0, ft_wordlen(s, c));
			if (!strs[i++])
				return (ft_free(strs));
			s += ft_wordlen(s, c);
		}
		else
			s++;
	}
	return (strs);
}

/*int main(void)
{
    char input[] = "This is a test string for splitting";
    char delimiter = ' ';
    char **result = ft_split(input, delimiter);

    if (result == NULL)
	{
        printf("Memory allocation failed or input string is NULL.\n");
        return 1;
    }

    printf("Split substrings:\n");
    int i = 0;
    while (result[i] != NULL)
	{
        int j = 0;
        while (result[i][j] != '\0')
		{
            printf("%c", result[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    i = 0;
    while (result[i] != NULL)
	{
        free(result[i]);
        i++;
    }
    free(result);

    return 0;
}*/