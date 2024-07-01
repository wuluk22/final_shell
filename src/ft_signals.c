/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:44:28 by clegros           #+#    #+#             */
/*   Updated: 2024/07/01 13:26:58 by yohanafi         ###   ########.fr       */
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
	//else if (sign == SIGQUIT)
	//{
	//	write(1, "\b\b  \b\b", 6); // Clear the "^\" characters printed by default
	//	rl_on_new_line();
	//	rl_replace_line("", 0);
	//	rl_redisplay();
	//}
}

void	ft_set_input_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, ft_signal_handler);
}

void	ft_set_dfl_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
