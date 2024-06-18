/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:06:17 by clegros           #+#    #+#             */
/*   Updated: 2024/06/18 17:44:52 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	ft_close(int *fd)
{
	close(*fd);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_cleanup_cmd_list(t_cmds *cmd_list)
{
	t_cmds	*temp;

	while (cmd_list)
	{
		if (cmd_list->str)
			ft_free_array(cmd_list->str);
		if (cmd_list->redirections)
			free(cmd_list->redirections);
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free(temp);
	}
}

t_cmds	*ft_create_cmd_node(void)
{
	t_cmds	*cmd;

	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	cmd->p_fd_input[0] = -1;
	cmd->p_fd_input[1] = -1;
	cmd->p_fd_output[0] = -1;
	cmd->p_fd_output[1] = -1;
	cmd->redirections = NULL;
	cmd->next = NULL;
	cmd->str = NULL;
	return (cmd);
}
