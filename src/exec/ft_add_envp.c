/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:24:35 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:39:04 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_transform(t_env *n_envp)
{
	char	**str;
	t_env	*head;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = NULL;
	head = n_envp;
	while (n_envp)
	{
		count++;
		if (n_envp->next == NULL)
			break ;
		n_envp = n_envp->next;
	}
	n_envp = head;
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (n_envp->next != NULL)
	{
		str[i] = ft_strdup(n_envp->key);
		str[i] = ft_strjoin(str[i], "=");
		str[i] = ft_strjoin(str[i], n_envp->value);
		i++;
		if (n_envp->next)
			n_envp = n_envp->next;
	}
	str[i] = NULL;
	n_envp = head;
	i = 0;
	return (str);
}

t_env	*ft_init_envp(char **envp, t_env *n_envp)
{
	int		i;
	int		j;
	int		k;
	char	**temp;
	t_env	*head;

	i = 0;
	j = 0;
	k = 1;
	head = n_envp;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		n_envp->key = ft_strdup(temp[0]);
		if (!ft_strncmp("LS_COLORS", temp[0], 9))
		{
			while (temp[k])
			{
				if (k == 1)
					n_envp->value = ft_strdup(temp[k]);
				else
					n_envp->value = ft_strjoin(n_envp->value, temp[k]);
				if (k < 12)
					n_envp->value = ft_strjoin(n_envp->value, "=");
				k++;
			}
		}
		else
		{
			n_envp->value = ft_strdup(temp[1]);
			if (!n_envp->value)
				return (NULL);
		}
		n_envp->next = NULL;
		while (temp[j])
		{
			temp[j++] = NULL;
		}
		i++;
		if (envp[i])
		{
			n_envp->next = malloc(sizeof(t_env));
			if (!n_envp->next)
				return (NULL);
			n_envp = n_envp->next;
		}
		j = 0;
		free(temp);
	}
	n_envp = head;
	return (n_envp);
}
