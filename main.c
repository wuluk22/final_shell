/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:04:56 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:21:51 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#define MEOW "\033[5m<-\033[0;35m(-x _ x-) \033[1;3;5;45mmini\033[1;3;5;37;45mshell\033[0;5m->\033[0m "

void	ft_cleanup_cmd_list(t_cmds *cmd_list)
{
	t_cmds	*temp;

	while (cmd_list)
	{
		if (cmd_list->str)
			free(cmd_list->str);
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free(temp);
	}
	free(cmd_list);
}

t_cmds *ft_create_cmd_node()
{
    t_cmds *cmd = malloc(sizeof(t_cmds));
    if (!cmd)
        return NULL;
    
    cmd->p_fd_input[0] = -1;
    cmd->p_fd_input[1] = -1;
    cmd->p_fd_output[0] = -1;
    cmd->p_fd_output[1] = -1;
    // Initialize other fields as necessary
    cmd->redirections = NULL;
    cmd->next = NULL;
    cmd->str = NULL;
    
    return cmd;
}


static void	ft_free_envp(t_env *n_envp)
{
    t_env *current = n_envp;
    t_env *next;

    while (current != NULL)
	{
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}

static int	ft_process_command(t_env **n_envp, char *line)
{
	t_lexer	*lexer_list;
	t_cmds	*cmd_list;

	lexer_list = NULL;
	cmd_list = NULL;
	/*lexer_list = malloc(sizeof(t_lexer));
	cmd_list = malloc(sizeof(t_cmds));
	cmd_list->str = NULL;
	cmd_list->builton = NULL;
	cmd_list->num_redirections = 0;
	cmd_list->p_fd_input[0] = 0;
	cmd_list->p_fd_input[1] = 0;
	cmd_list->p_fd_output[0] = 0;
	cmd_list->p_fd_output[1] = 0;
	cmd_list->pid = 0;
	cmd_list->hd_file_name = NULL;
	cmd_list->redirections = NULL;
	cmd_list->next = NULL;
	cmd_list->prev = NULL;
	cmd_list->envp = NULL;
	cmd_list->exit = 0;*/

	/*cmd_list->p_fd_input[0] = 0;
	cmd_list->p_fd_input[1] = 0;
	cmd_list->p_fd_output[0] = 0;
	cmd_list->p_fd_output[1] = 0;*/
	if (!line)
	{
		perror("error reading command");
		return (0);
	}
	ft_tokenize(&lexer_list, line);
	ft_lexer_to_cmds(&cmd_list, &lexer_list);
	if (cmd_list)
		ft_expander(cmd_list);
	if (ft_b_ins(cmd_list, lexer_list, n_envp) == 1)
		return (1);
	ft_cleanup_cmd_list(cmd_list);
	ft_free_list(lexer_list);
	return (0);
}

void	minishell_loop(char **envp, char *line)
{
	t_env	*n_envp;

	n_envp = NULL;
	n_envp = malloc(sizeof(t_env));
	if (!n_envp)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	n_envp->key = NULL;
	n_envp->value = NULL;
	n_envp->next = NULL;
	n_envp->env = NULL;
	n_envp = ft_init_envp(n_envp, envp);
	//ft_transform(n_envp);
	while (1)
	{
		ft_set_input_signals();
		line = readline(MEOW);
		if (!line)
			break ;
		add_history(line);
		if (ft_process_command(&n_envp, line))
		{
			free(line);
			break ;
		}
		if (line)
			free(line);
	}
	ft_free_envp(n_envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	line = malloc(sizeof(char *));
	line = NULL;
	minishell_loop(envp, line);
	return (EXIT_SUCCESS);
}
//system("leaks ./minishell");
