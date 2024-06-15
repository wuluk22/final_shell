/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:40:31 by clegros           #+#    #+#             */
/*   Updated: 2024/06/14 18:40:33 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmds *cmd)
{
	char	*crt_wd;

	crt_wd = NULL;
	(void)cmd;
	crt_wd = getcwd(crt_wd, sizeof(size_t));
	printf("%s\n", crt_wd);
	return (0);
}
