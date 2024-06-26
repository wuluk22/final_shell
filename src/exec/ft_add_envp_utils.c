/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_envp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:59:31 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 13:01:34 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_handle_ls_colors(char **temp)
{
	char	*value;
	char	*tmp;
	int		k;

	k = 1;
	value = ft_strdup(temp[k]);
	k++;
	while (temp[k])
	{
		tmp = value;
		value = ft_strjoin(tmp, temp[k]);
		free(tmp);
		if (k < 12)
		{
			tmp = value;
			value = ft_strjoin(value, "=");
			free(tmp);
		}
		k++;
	}
	return (value);
}

static t_env	*ft_init_node(t_env *n_envp, char **temp)
{
	if (!ft_strncmp("LS_COLORS", temp[0], 9))
		n_envp->value = ft_handle_ls_colors(temp);
	else
	{
		n_envp->value = ft_strdup(temp[1]);
		if (!n_envp->value)
			return (NULL);
	}
	n_envp->next = NULL;
	return (n_envp);
}

static void	ft_free_temp_array(char **temp)
{
	int	j;

	j = 0;
	while (temp[j])
	{
		free(temp[j]);
		j++;
	}
	free(temp);
}

t_env	*ft_init_envp(t_env *n_envp, t_env *head, char **envp, int i)
{
	char	**temp;

	head = n_envp;
	while (envp[++i])
	{
		temp = ft_split(envp[i], '=');
		n_envp->key = ft_strdup(temp[0]);
		n_envp = ft_init_node(n_envp, temp);
		if (!n_envp || !n_envp->key || !temp)
		{
			ft_free_temp_array(temp);
			return (NULL);
		}
		if (envp[i + 1])
		{
			n_envp->next = malloc(sizeof(t_env));
			if (n_envp->next == NULL)
				return (NULL);
			n_envp = n_envp->next;
		}
		ft_free_temp_array(temp);
	}
	return (head);
}
