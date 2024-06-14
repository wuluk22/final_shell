#include "../../includes/minishell.h"

char	**ft_transform(t_env *n_envp)
{
	char	**str;
	//char	*temp;
	//char	*temp2;
	t_env	*head;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = NULL;
	head = n_envp;
	while (n_envp)
	{
		count++;
		if (n_envp->next == NULL)
			break ;
		n_envp = n_envp->next;
	}
	n_envp = head;
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	//write(2, "yo\n", 3);
	while (n_envp->next != NULL)
	{
		//printf("--%s--\n", n_envp->key);
		str[i] = ft_strdup(n_envp->key);
		str[i] = ft_strjoin(str[i], "=");
		str[i] = ft_strjoin(str[i], n_envp->value);
		i++;
		if (n_envp->next)
			n_envp = n_envp->next;
	}
	str[i] = NULL;
	n_envp = head;
	i = 0;
	/*while (str[i])
	{
		printf("--%s--\n", str[i]);
		i++;
	}*/
	return (str);
}

t_env	*ft_init_envp(char **envp, t_env *n_envp)
{
	int		i;
	int		j;
	int		k;
	char	**temp;
	t_env	*head;

	i = 0;
	j = 0;
	k = 1;
	//n_envp = malloc(sizeof(t_env *));
	head = n_envp;
	while(envp[i])
	{
		temp = ft_split(envp[i], '=');
		//printf("--yo--%s\n", temp[0]);
		n_envp->key = ft_strdup(temp[0]);
		if (!ft_strncmp("LS_COLORS", temp[0], 9))
		{
			while (temp[k])
			{
				if (k == 1)
					n_envp->value = ft_strdup(temp[k]);
				else
					n_envp->value = ft_strjoin(n_envp->value, temp[k]);
				if (k < 12)
					n_envp->value = ft_strjoin(n_envp->value, "=");
				k++;
			}
		}
		else
		{
			n_envp->value = ft_strdup(temp[1]);
			if (!n_envp->value)
				return (NULL);
		}
		n_envp->next = NULL;
		while (temp[j])
		{
			temp[j++] = NULL;
		}
		i++;
		if (envp[i])
        {
            n_envp->next = malloc(sizeof(t_env));
            if (!n_envp->next)
                return (NULL);
            n_envp = n_envp->next;
        }
		j = 0;
		free(temp);
	}
	n_envp = head;
	/*while (n_envp->next != NULL)
	{
		printf("--key:%s    --val:%s\n", n_envp->key, n_envp->value);
		if (n_envp->next)
			n_envp = n_envp->next;
	}*/
	//write(2, "yi\n", 3);
	return (n_envp);
}