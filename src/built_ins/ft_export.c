#include "../../includes/minishell.h"

/*static int	ft_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}*/
/*
static void	ft_del_quotes(t_simple_cmds *cmd)
{

}

static void	ft_check_param(t_simple_cmds *cmd, char **env_p)
{
	if (ft_equal_sign(cmd->str[1]) == 0)
		return (EXIT_FAILURE);
	
}

static void	ft_var_exist(t_simple_cmds *cmd, char **env_p)
{

}
*/
/*static char	**add_loop(t_env *n_envp, char **ret, char *var)
{
	int	i;

	i = 0;
	while (n_envp)
	{
		ret[i] = ft_strdup(n_envp->key);
		if (ret[i] == NULL)
		{
			free(ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = ft_strdup(var);
	if (ret[i] == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret[i + 1] = NULL;
	while (ret[i])
	{
		write(1, ret[i], ft_strlen(ret[i]));
		write(1, "\n", 1);
		i++;
	}
	return (ret);
}
static t_env	*ft_add_var(t_env *n_envp, char *var)
{
	char	**ret;
	int		i;
	int		pos;

	i = 1;
	pos = ft_equal_sign(var);
	if (var[pos] == '\'')
		delete_quotes(var + pos, '\'');
	if (var[pos] == '\"')
		delete_quotes(var + pos, '\"');
	while (envp[i] != NULL)
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (NULL);
	
	return (add_loop(n_envp, ret, var));
}*/

t_env	*ft_export(t_simple_cmds *cmd, t_env *n_envp)
{
	int		i;
	int		j;
	//char	**temp;

	
	i = 1;
	j = 0;
	(void)n_envp;
	while (cmd->str[i])
	{
		if (cmd->str[i])
		{
			//n_envp = ft_add_var(n_envp, cmd->str[i]);
			//if (!temp)
			//	return (NULL);
			/*while (envpp->env[j])
				free(envpp->env[j++]);
			free (envpp->env);*/
			//n_envp = temp;
		}
		i++;
	}
	i = 0;
	/*while (n_envp)
	{
		write(1, envpp->env[i], ft_strlen(envpp->env[i]));
		write(1, "\n", 1);
		//free(env_p[i]);
		i++;
	}*/
	//free(env_p);
		//
	//while (temp[0])
	//printf("\n\n%s\n", temp[0]);
	return (n_envp);
}