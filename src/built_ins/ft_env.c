/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:41:52 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:41:56 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("%s\n", str[i]);
		i++;
	}
	return (0);
}
