/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:24:45 by clegros           #+#    #+#             */
/*   Updated: 2024/06/21 16:32:39 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env_value(t_env *n_envp, const char *var_name)
{
	char	*value;
	t_env	*current;

	current = NULL;
	value = NULL;
	current = n_envp;
	while(current)
	{
		if (!ft_strncmp(current->key, var_name, ft_strlen(var_name)) 
			&& ft_strlen(var_name) == ft_strlen(current->key))
			value = current->value;
		else
			value = "\n";
		current = current->next;
	}
	return (value);
}

int	ft_count_occurrences(const char *str, const char *old_substr)
{
	int			count;
	int			oldlen;
	const char	*temp;

	count = 0;
	oldlen = ft_strlen(old_substr);
	temp = str;
	while (1)
	{
		temp = ft_strnstr(temp, old_substr, ft_strlen(old_substr));
		if (!temp)
			break ;
		count++;
		temp += oldlen;
	}
	return (count);
}

void	ft_delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

char	*ft_allocate_result(char *str, char *old_substr, char *new_substr)
{
	int		count;
	int		newlen;
	int		oldlen;
	char	*result;

	count = ft_count_occurrences(str, old_substr);
	newlen = ft_strlen(new_substr);
	oldlen = ft_strlen(old_substr);
	result = (char *)malloc(ft_strlen(str) + count * (newlen - oldlen) + 1);
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (result);
}

char	*ft_replace_substr(char *str, char *old_substr, char *new_substr)
{
	char	*result;
	int		i;
	int		oldlen;
	int		newlen;

	result = ft_allocate_result(str, old_substr, new_substr);
	i = 0;
	oldlen = ft_strlen(old_substr);
	newlen = ft_strlen(new_substr);
	while (*str)
	{
		if (ft_strnstr(str, old_substr, ft_strlen(old_substr)) == str)
		{
			strcpy(&result[i], new_substr);
			i += newlen;
			str += oldlen;
		}
		else
			result[i++] = *str++;
	}
	result[i] = '\0';
	return (result);
}
