/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipe2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:02:01 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/07 23:56:32 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_second_parse	*inside_parent_multi_pipe(t_second_parse *temp, t_minishell *m)
{
	while (temp != NULL && temp->value != EXP)
	{
		if (temp->value == _R_INPUT_2 || temp->value == _DELIMITEUR_2)
			m->mp.i++;
		temp = temp->next;
	}
	if (temp != NULL && temp->value == EXP)
		dup2(m->mp.pipefd[0], m->mp.fd_in);
	close(m->mp.pipefd[0]);
	close(m->mp.pipefd[1]);
	while (temp != NULL && temp->value != _PIPE)
		temp = temp->next;
	if (temp != NULL && temp->value == _PIPE)
		temp = temp->next;
	return (temp);
}
