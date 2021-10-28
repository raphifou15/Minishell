/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_reboot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 05:02:11 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/28 05:10:41 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reboot(t_minishell *m, char *line)
{
	destroy_all(m, line, m->use);
	m->use = 0;
	dup2(m->r.fd_out_save, STDOUT_FILENO);
	close(m->r.fd_out_save);
	dup2(m->r.fd_in_save, STDIN_FILENO);
	close(m->r.fd_in_save);
}
