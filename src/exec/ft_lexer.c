/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:09:28 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 16:05:38 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_duplicate_path(const char *path)
{
	if (path == NULL)
		return (NULL);
	return (ft_strdup(path));
}

static size_t	ft_token_length(const char *token)
{
	size_t	len;

	len = 0;
	while (token[len] != '\0' && token[len] != ':')
		len++;
	return (len);
}

static int	ft_check_access(const char *token, const char *command)
{
	size_t	command_len;
	size_t	token_len;
	char	*full_path;

	command_len = ft_strlen(command);
	while (*token != '\0')
	{
		token_len = ft_token_length(token);
		full_path = malloc(token_len + command_len + 2);
		if (!full_path)
			return (0);
		memcpy(full_path, token, token_len);
		full_path[token_len] = '/';
		memcpy(full_path + token_len + 1, command, command_len + 1);
		if (access(full_path, X_OK) == 0)
			return (1);
		token += token_len;
		if (*token == ':')
			token++;
	}
	return (0);
}

static int	ft_is_command_valid(const char *command)
{
	char	*path;
	char	*path_copy;
	char	*token;
	int		result;

	//getenv ??
	path = getenv("PATH");
	path_copy = ft_duplicate_path(path);
	if (path_copy == NULL)
		return (0);
	token = path_copy;
	result = ft_check_access(token, command);
	free(path_copy);
	return (result);
}

t_pipex	ft_dispatch(t_pipex exec, char *arg)
{
	char	**args;

	args = ft_split(arg, ' ');
	if (arg)
	{
		if (ft_is_command_valid(args[0]))
		{
			exec.cmd_args = &args[0];
			exec.cmd = ft_parsing(exec.cmd_paths, *exec.cmd_args);
		}
	}
	return (exec);
}
/*static t_lexer	*ft_parser(t_lexer *list)
{
	t_lexer	*head;

	head = NULL;
	while (list)
	{
		if ((ft_strncmp(list->str, "$", 1) == 0) && (!list->str[1]))
		{
			list = list->next;
			if (ft_strncmp(list->next->str, "=", 1) == 0)
			{
				list->chr = "n";
				list = list->next->next;
				list->chr = "e";
			}
			else
				list->chr = "E";
		}
		list = list->next;
	}
	return (head);
}*/
