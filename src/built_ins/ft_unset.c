#include "../../includes/minishell.h"

static t_env	*ft_remove(t_simple_cmds *cmd, t_env **n_envp)
{
	t_env	*current;
	t_env	*head;
	t_env	*new_envp;
	t_env	*new_node;

	current = *n_envp;
	new_envp = NULL;
	while (current)
	{
		if (!ft_strncmp(current->key, cmd->str[1], ft_strlen(cmd->str[1])))
		{
			current->key = NULL;
			current->value = NULL;
			//printf("%s\n", current->key);
		}
		if (current->key != NULL)
		{
			new_node = malloc(sizeof(t_env));
			new_node->key = current->key;
			new_node->value = current->value;
			new_node->next = NULL;
			if (new_envp == NULL)
			{
				new_envp = new_node;
				head = new_envp;
			}
			else
			{
				new_envp->next = new_node;
				new_envp = new_envp->next;
			}
			//printf("------------1");
		}
		if (current->next == NULL)
			break;
		current = current->next;
	}
	return (head);

}

t_env	*ft_unset(t_simple_cmds *cmd, t_env *n_envp)
{
	n_envp = ft_remove(cmd, &n_envp);
	return (n_envp);
}