/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipe2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:02:01 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/15 03:41:16 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_second_parse	*inside_parent_multi_pipe(t_second_parse *temp, t_minishell *m)
{
	while (temp != NULL && temp->value != EXP && temp->value != _PIPE)
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

void	boucle_pipe_fork(int nbr_pipe, t_minishell *m, t_second_parse *temp,
			char *line)
{
	int	i;

	i = -1;
	while (++i <= nbr_pipe && g_signal == 0)
	{
		if (pipe(m->mp.pipefd) < 0)
			return (good_return_multipipe_2(m, errno));
		m->mp.pid[i] = fork();
		if (m->mp.pid[i] < 0)
			return (good_return_multipipe_3(m, errno));
		if (m->mp.pid[i] == 0)
			executing_inside_child_multi_pipe(temp, m, i, line);
		temp = inside_parent_multi_pipe(temp, m);
	}
	reboot_executing_with_pipe(m);
}
