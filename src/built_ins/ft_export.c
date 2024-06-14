#include "../../includes/minishell.h"

static t_env	*ft_add_envp(t_env **n_envp, char **args)
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
			//ft_env(NULL, current);
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
	//current->next = malloc(sizeof(t_env));
	if (head)
		new_node->next = head;
	//n_envp = n_envp->next;
	//printf("--%s--  --%s--\n", n_envp->key, n_envp->value);
	//ft_env(NULL, current);
	return (new_node);
}

t_env	*ft_export(t_simple_cmds *cmd, t_env *n_envp)
{
	char	**args;

	args = NULL;
	args = ft_split(cmd->str[1], '=');
	n_envp = ft_add_envp(&n_envp, args);
	ft_env(NULL, n_envp);
	free(args[0]);
	free(args[1]);
	free(args);
	return (n_envp);
}