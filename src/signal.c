/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 04:06:53 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/08 21:07:17 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_begin(t_minishell *m, char *line)
{
	if (g_signal != 0)
	{
		m->retour = g_signal;
		g_signal = 0;
	}
	if (line == NULL)
	{
		ft_putstr(" exit\n");
		ft_free_all_elem_env(m->e);
		close(2);
		close(1);
		close(0);
		exit(0);
	}
}

void	signal_end(t_minishell *m)
{
	if (g_signal != 0)
		m->retour = g_signal;
	g_signal = 0;
}

void	signal_default(void)
{
	signal(SIGINT, handler_default);
	signal(SIGQUIT, SIG_IGN);
}
