/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:06:17 by clegros           #+#    #+#             */
/*   Updated: 2024/02/07 14:30:17 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	ft_close(int *fd)
{
	close(*fd);
	//*fd = -1;
}

void ft_free_array(char **array)
{
    int i;

    if (array == NULL)
        return;

    i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
}
