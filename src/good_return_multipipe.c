/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_return_multipipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:45:11 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/12 21:08:21 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	good_return_multipipe_1(t_minishell *m, int err, int x)
{
	if (x == 0)
	{
		error2(err);
		m->retour = 1;
		return ;
	}
	if (x == 1)
	{
		close(m->mp.fd_in);
		return ;
	}
}
