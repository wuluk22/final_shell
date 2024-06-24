/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:44:28 by clegros           #+#    #+#             */
/*   Updated: 2024/05/29 14:09:26 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_global = 1;
	}
	/*else if (sign == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}*/
}

void	ft_set_input_signals(void)
{
	//signal(SIGQUIT, ft_signal_handler);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

//void	ft_signal_handler2(int sign)
//{
//	if (sign == SIGINT)
//		ft_putendl_fd("", 1);
//}
