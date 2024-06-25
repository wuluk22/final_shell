#include "libft.h"

static void	*ft_memalloc(size_t size)
{
	char	*alloc;

	alloc = (char*)malloc(size + 1);
	if (alloc && size < 2147483647)
	{
		ft_memset(alloc, 0, size);
		return (alloc);
	}
	else
		return (0);
}

static char	*ltrim(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

static char	*rtrim(char *str)
{
	char	*end;

	if (!str)
		return (NULL);
	end = str + ft_strlen(str) - 1;
	while (end >= str && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

static char	*ft_trim(char *str)
{
	if (!str)
		return (NULL);
	return (rtrim(ltrim(str)));
}

static int		ft_word_len(char const *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (!ft_isspace((unsigned char)s[i]))
		{
			len++;
			while (s[i] && !ft_isspace((unsigned char)s[i]))
				i++;
		}
		else
			i++;
	}
	return (len);
}

static void	ft_copy_trimmed(char *dest, char *src)
{
	int	i;
	int	j;
	int	space;

	i = 0;
	j = 0;
	space = 0;
	while (src[i])
	{
		if (!ft_isspace((unsigned char)src[i]))
		{
			if (space && j > 0)
				dest[j++] = ' ';
			space = 0;
			while (src[i] && !ft_isspace((unsigned char)src[i]))
				dest[j++] = src[i++];
		}
		else
		{
			space = 1;
			i++;
		}
	}
	dest[j] = '\0';
}

char	*ft_whitespaces(char *s)
{
	char	*trimmed;
	char	*new_str;
	int		new_len;

	if (!s)
		return (NULL);

	trimmed = ft_trim(s);
	if (!trimmed)
		return (NULL);

	new_len = ft_word_len(trimmed);
	if (!(new_str = (char*)ft_memalloc(new_len + 1)))
		return (NULL);

	ft_copy_trimmed(new_str, trimmed);
	return (new_str);
}
