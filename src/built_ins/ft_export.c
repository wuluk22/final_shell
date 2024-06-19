/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:40 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:23:52 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static t_env	*ft_add_envp(t_env **n_envp, char **args)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	head = *n_envp;
	current = *n_envp;
	while (current)
	{
		if (ft_strncmp(current->key, args[0], ft_strlen(args[0])) == 0)
		{
			free(current->value);
			current->value = ft_strdup(args[1]);
			current = head;
			return (current);
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(args[0]);
	new_node->value = ft_strdup(args[1]);
	new_node->next = NULL;
	if (head)
		new_node->next = head;
	return (new_node);
}*/

static t_env	*ft_find_and_update_envp(t_env *head, char **args)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strncmp(current->key, args[0], ft_strlen(args[0])) == 0)
		{
			free(current->value);
			current->value = ft_strdup(args[1]);
			return (head);
		}
		current = current->next;
	}
	return (NULL);
}

static t_env	*ft_create_new_node(char **args)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(args[0]);
	new_node->value = ft_strdup(args[1]);
	new_node->next = NULL;
	return (new_node);
}

static t_env	*ft_add_envp(t_env **n_envp, char **args)
{
	t_env	*head;
	t_env	*new_node;

	head = *n_envp;
	if (ft_find_and_update_envp(head, args))
		return (head);
	new_node = ft_create_new_node(args);
	if (!new_node)
		return (NULL);
	new_node->next = head;
	return (new_node);
}

t_env	*ft_export(t_cmds *cmd, t_env *n_envp)
{
	char	**args;

	args = NULL;
	if (cmd->str[1])
	{
		args = ft_split(cmd->str[1], '=');
		if (!args[1])
		{
			free(args[1]);
			args[1] = ft_strdup("");
		}
		n_envp = ft_add_envp(&n_envp, args);
	}
	else
		ft_env(NULL, n_envp);
	if (args)
	{
		free(args[0]);
		free(args[1]);
		free(args);
	}
	return (n_envp);
}
