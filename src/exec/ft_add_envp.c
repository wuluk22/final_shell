/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:24:35 by clegros           #+#    #+#             */
/*   Updated: 2024/06/19 12:50:21 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_nodes(t_env *n_envp)
{
	int	count;

	count = 0;
	while (n_envp)
	{
		count++;
		n_envp = n_envp->next;
	}
	return (count);
}

static char	**ft_allocate_str_array(int count)
{
	char	**str;

	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (str);
}

static char	**ft_populate_str_array(t_env *n_envp, char **str)
{
	int	i;

	i = 0;
	while (n_envp)
	{
		str[i] = ft_strdup(n_envp->key);
		str[i] = ft_strjoin(str[i], "=");
		str[i] = ft_strjoin(str[i], n_envp->value);
		i++;
		n_envp = n_envp->next;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_transform(t_env *n_envp)
{
	int		count;
	char	**str;

	count = ft_count_nodes(n_envp);
	str = ft_allocate_str_array(count);
	if (!str)
		return (NULL);
	str = ft_populate_str_array(n_envp, str);
	return (str);
}
