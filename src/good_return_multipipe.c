/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_return_multipipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:45:11 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 01:22:36 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	good_return_multipipe_1(t_minishell *m, int err, int x)
{
	int	j;

	if (x == 0)
	{
		error2(err);
		m->retour = 1;
		return ;
	}
	if (x == 1)
	{
		j = -1;
		while (++j < (m->mp.j))
			close(m->mp.fds[j]);
		if (g_signal != 0)
			free(m->mp.fds);
		free(m->mp.pid);
		close(m->mp.fd_in);
		return ;
	}
	if (x == 2)
	{
		error1(0);
		close (m->mp.fd_in);
		m->retour = 1;
	}
}

void	good_return_multipipe_2(t_minishell *m, int err)
{
	int	j;

	j = -1;
	while (++j < m->mp.j)
		close(m->mp.fds[j]);
	free(m->mp.fds);
	free(m->mp.pid);
	close(m->mp.fd_in);
	error2(err);
	m->retour = 1;
}

void	good_return_multipipe_3(t_minishell *m, int err)
{
	int	j;

	j = -1;
	while (++j < m->mp.j)
		close(m->mp.fds[j]);
	close(m->mp.pipefd[0]);
	close(m->mp.pipefd[1]);
	free(m->mp.fds);
	free(m->mp.pid);
	close(m->mp.fd_in);
	error2(err);
	m->retour = 1;
}
