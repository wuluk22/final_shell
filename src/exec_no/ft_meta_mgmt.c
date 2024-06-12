/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meta_mgmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:35:53 by clegros           #+#    #+#             */
/*   Updated: 2024/05/29 14:42:10 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_meta_str(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '|')
		return (3);
	else
		return (0);
}

int	list_parkour_str(char *list)
{
	int	i;
	int	j;
	int	meta;

	i = 0;
	j = 0;
	meta = 0;
	while (*list != '\0')
	{
		if (ft_meta_str(*list) > 0)
		{
			if (ft_meta_str(*list) == 1)
				meta = 1;
			else if (ft_meta_str(*list) == 2)
				meta = 2;
			else if (ft_meta_str(*list) == 3)
				meta = 3;
			i++;
		}
		list++;
	}
	return (i);
}

static int	process_lexer_list(t_lexer *list, char **args)
{
	int	arg_count;

	arg_count = 0;
	while (list)
	{
		if (list && ft_meta(list->token) == 0)
		{
			if (arg_count < 100)
				args[arg_count++] = list->token;
			list = list->next;
		}
		else if (list && ft_meta(list->token) > 0)
		{
			list->chr = "m";
			args[arg_count++] = list->token;
			list = list->next;
		}
	}
	return (arg_count);
}

void	ft_meta_mgmt(char *cmd, char **envp)
{
	t_lexer	*list;
	char	*args[100];

	list = NULL;
	tokenize(cmd, &list);
	if (list_parkour(list) >= 1)
	{
		process_lexer_list(list, args);
		ft_first_iter(args, envp);
	}
}

/*static int	ft_meta_str(char *c)
{
	if (strcmp(c, "<") == 0)
		return (1);
	if (strcmp(c, ">") == 0)
		return (2);
	if (strcmp(c, "<<") == 0)
		return (3);
	if (strcmp(c, ">>") == 0)
		return (4);
	if (strcmp(c, "|") == 0)
		return (5);
	else
		return (0);
}

static int	list_parkour_str(char *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (list)
	{
		if (ft_meta(list[j++]) > 0)
			i++;
		list++;
		printf("list---%s\n", list);
	}
	return (i);
}*/

/*void	ft_meta_mgmt(char *cmd, char **envp)
{
	int		i;
	char	*args[100];
	int		arg_count;
	t_lexer	*list;

	i = 0;
	list = NULL;
	arg_count = 0;
	tokenize(cmd, &list);
	if (list_parkour(list) >= 1)
	{
		while (list)
		{
			if (list && ft_meta(list->token) == 0)
			{
				if (arg_count <= 100)
					args[arg_count++] = list->token;
				list = list->next;
			}
			else if (list && ft_meta(list->token) > 0)
			{
				list->chr = "m";
				args[arg_count++] = list->token;
				list = list->next;
			}
			i++;
		}
		ft_first_iter(args, envp);
	}
}*/
