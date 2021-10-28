/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:46:15 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/28 05:10:38 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirection(t_minishell *m, char *line)
{
	(void)line;
	m->r.i = 0;
	m->r.error = 0;
	m->r.fd_out_save = dup(STDOUT_FILENO);
	m->r.fd_in_save = dup(STDIN_FILENO);
}
