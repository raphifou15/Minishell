/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_reboot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 05:02:11 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/13 05:31:06 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reboot(t_minishell *m, char *line)
{
	destroy_all(m, line, m->use);
	if (m->use == 0)
	{
		dup2(m->r.fd_out_save, STDOUT_FILENO);
		close(m->r.fd_out_save);
		dup2(m->r.fd_in_save, STDIN_FILENO);
		close(m->r.fd_in_save);
	}
	m->use = 0;
}

void	reboot_executing_with_pipe(t_minishell *m)
{
	int	j;
	int	i;

	j = -1;
	close(m->mp.fd_in);
	while (++j < m->mp.j)
		close(m->mp.fds[j]);
	i = -1;
	while (++i <= m->mp.nbr_p)
		wait(NULL);
	free(m->mp.fds);
	m->mp.fds = NULL;
}
