/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:48:15 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 15:20:47 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer_to_cmds(t_cmds **cmd_list, t_lexer **tokens)
{
	while (*tokens != NULL)
		ft_parse_command(cmd_list, tokens);
}

void	ft_free_cmds(t_cmds *cmds)
{
	t_cmds	*temp;

	while (cmds != NULL)
	{
		temp = cmds;
		cmds = cmds->next;
		free(temp->str);
		ft_free_list(temp->redirections);
		free(temp);
	}
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;

	if (*needle == '\0')
		return ((char *)haystack);
	len = ft_strlen(needle);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
