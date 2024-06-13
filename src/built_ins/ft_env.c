#include "../../includes/minishell.h"

int	ft_env(t_simple_cmds *cmd, t_env *n_envp)
{
	(void)cmd;
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	str = ft_transform(n_envp);
	while (str[i])	
	{
		printf("|-%s\n", str[i]);
		i++;
	}
	return (0);
}