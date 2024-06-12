#include "../../includes/minishell.h"

int	ft_env(t_simple_cmds *cmd, char **env_p, t_env *envpp)
{
	(void)cmd;
	(void)env_p;
	int	i;

	i = 0;
	while(envpp->env[i])
	{
		if (envpp->env[i])
		{
			printf("-%s\n", envpp->env[i]);
		}
		i++;
	}
	return (0);
}