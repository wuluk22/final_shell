/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:05:23 by clegros           #+#    #+#             */
/*   Updated: 2024/05/31 13:05:21 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static void	here_txt(char *argv, int *p_fd)
{
	char	*line;

	//printf("6");
	close(p_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		//printf("%s", line);
		if (!line)
			exit(EXIT_FAILURE);
		if (!ft_strncmp(line, argv, ft_strlen(argv)))
		{
			//printf("0\n");
			printf("line %s\n", line);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, p_fd[1]);
		free(line);
	}
}

static void	here_doc(char *argv)
{
	pid_t	pid;
	int		p_fd[2];
	//printf("4");
	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
		here_txt(argv, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(0);
	}
}*/

static int	ft_count_tokens(t_lexer *tokens)
{
	int		count;
	t_lexer	*temp;

	count = 0;
	temp = tokens;
	while (temp != NULL && ft_strncmp(temp->token, "|", 1) != 0)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static void	ft_fill_command_strings(t_lexer **tokens, t_cmds *new_cmd)
{
	t_lexer	*current;
	int		i;

	current = *tokens;
	i = 0;
	while (current != NULL && ft_strncmp(current->token, "|", 1) != 0)
	{
		ft_strtrim(current->token, " ");
		new_cmd->str[i++] = current->token;
		current = current->next;
	}
	new_cmd->str[i] = NULL;
	*tokens = current;
}

void	ft_parse_command(t_cmds **cmd_list, t_lexer **tokens)
{
	t_lexer	*current;
	t_lexer	*cmd_start;
	t_lexer	*redirections;
	t_cmds	*new_cmd;
	int		token_count;

	current = *tokens;
	cmd_start = current;
	redirections = NULL;
	new_cmd = ft_create_simple_cmd_node();
	token_count = ft_count_tokens(current);
	new_cmd->str = (char **)malloc(sizeof(char *) * (token_count + 1));
	ft_parse_redirections(&cmd_start, &redirections);
	if (new_cmd->str == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	ft_fill_command_strings(&current, new_cmd);
	new_cmd->redirections = redirections;
	ft_add_spl_cmd(cmd_list, new_cmd);
	if (current != NULL && ft_strncmp(current->token, "|", 1) == 0)
		*tokens = current->next;
	else
		*tokens = current;
}

/*void	parse_command(t_lexer **tokens, t_simple_cmds **cmd_list)
{
	t_lexer			*current;
	t_lexer			*cmd_start;
	t_lexer			*redirections;
	t_simple_cmds	*new_cmd;
	int				token_count;
	t_lexer			*temp;
	int				i;

	current = *tokens;
	cmd_start = current;
	redirections = NULL;
	new_cmd = create_simple_cmd_node();
	token_count = 0;
	i = 0;
	parse_redirections(&cmd_start, &redirections);
	temp = current;
	while (temp != NULL && ft_strncmp(temp->token, "|", 1) != 0)
	{
		token_count++;
		temp = temp->next;
	}
	new_cmd->str = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (new_cmd->str == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (current != NULL && strcmp(current->token, "|") != 0)
	{
		ft_strtrim(current->token, " ");
		new_cmd->str[i++] = current->token;
		current = current->next;
	}
	new_cmd->str[i] = NULL;
//if (new_cmd->str[0] != NULL && is_builtin(new_cmd->str[0])) {
// Assign the corresponding function pointer to new_cmd->builtin
// Example: new_cmd->builtin = &builtin_function;
//}
	new_cmd->redirections = redirections;
	add_spl_cmd(cmd_list, new_cmd);
	if (current != NULL && strcmp(current->token, "|") == 0)
		*tokens = current->next;
	else
		*tokens = current;
}*/
