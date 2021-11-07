/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 04:19:22 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/07 04:31:47 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_default(int nb)
{
	if (nb == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr(" \n");
		rl_redisplay();
		g_signal = 130;
	}
}

void	handler_inside_child(int nb)
{
	if (nb == SIGINT)
		ft_putstr("\n");
	if (nb == SIGQUIT)
		ft_putstr("Quit (core dumped)\n");
}

void	handler_heredoc(int nb)
{
	if (nb == SIGINT)
	{
		ft_putstr("\n");
		g_signal = 130;
		close(STDIN_FILENO);
	}
}
