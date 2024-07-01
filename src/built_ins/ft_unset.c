/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:24:08 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 13:00:27 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*ft_remove_node(t_cmds *cmd, t_env *head)
{
	t_env	*current;
	t_env	*previous;

	current = head;
	previous = NULL;
	while (current)
	{
		if (!ft_strncmp(current->key, cmd->str[1], ft_strlen(cmd->str[1])))
		{
			if (previous)
				previous->next = current->next;
			else
				head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (head);
		}
		previous = current;
		current = current->next;
	}
	return (head);
}

static t_env	*ft_create_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

static void	ft_add_node(t_env **n_head, t_env **n_node, char *key, char *value)
{
	if (!*n_head)
	{
		*n_head = ft_create_node(key, value);
		if (!*n_head)
			return ;
		*n_node = *n_head;
	}
	else
	{
		(*n_node)->next = ft_create_node(key, value);
		if (!(*n_node)->next)
			return ;
		*n_node = (*n_node)->next;
	}
}

static t_env	*ft_copy_envp(t_env *head)
{
	t_env	*new_head;
	t_env	*new_node;
	t_env	*current;

	new_head = NULL;
	new_node = NULL;
	current = head;
	while (current)
	{
		if (current->key != NULL)
		{
			ft_add_node(&new_head, &new_node, current->key, current->value);
		}
		current = current->next;
	}
	return (new_head);
}

t_env	*ft_unset(t_cmds *cmd, t_env *n_envp)
{
	if (!cmd->str[1])
		return (ft_copy_envp(n_envp));
	n_envp = ft_remove_node(cmd, n_envp);
	return (ft_copy_envp(n_envp));
}
