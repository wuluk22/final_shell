/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:40 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 15:22:44 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*ft_find_and_update_envp(t_env *head, char **args, int append)
{
	t_env	*current;
	char	*new_value;

	current = head;
	while (current)
	{
		if (ft_strncmp(current->key, args[0], ft_strlen(args[0])) == 0)
		{
			if (append)
			{
				new_value = ft_strjoin(current->value, args[1]);
				free(current->value);
				current->value = new_value;
			}
			else
			{
				free(current->value);
				current->value = ft_strdup(args[1]);
			}
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

static t_env	*ft_add_envp(t_env **n_envp, char **args, int append)
{
	t_env	*head;
	t_env	*new_node;

	head = *n_envp;
	if (ft_find_and_update_envp(head, args, append))
		return (head);
	new_node = ft_create_new_node(args);
	if (!new_node)
		return (NULL);
	new_node->next = head;
	return (new_node);
}

static char	**ft_parse_args(char *str, int *append)
{
	char	**args;
	char	*pos;

	*append = 0;
	pos = ft_strstr(str, "+=");
	if (pos)
	{
		args = malloc(sizeof(char *) * 3);
		if (!args)
			return (NULL);
		args[0] = ft_strndup(str, pos - str);
		args[1] = ft_strdup(pos + 2);
		args[2] = NULL;
		*append = 1;
	}
	else
	{
		args = ft_split(str, '=');
		if (!args[1])
		{
			free(args[1]);
			args[1] = ft_strdup("");
		}
	}
	return (args);
}

t_env	*ft_export(t_cmds *cmd, t_env *n_envp)
{
	char	**args;
	int		append;

	args = NULL;
	if (cmd->str[1])
	{
		args = ft_parse_args(cmd->str[1], &append);
		if (args)
		{
			n_envp = ft_add_envp(&n_envp, args, append);
			free(args[0]);
			free(args[1]);
			free(args);
		}
	}
	else
		ft_env(NULL, n_envp);
	return (n_envp);
}
