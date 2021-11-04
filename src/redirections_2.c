/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:46:15 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/03 04:26:26 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_nbr_out(t_second_parse *begin)
{
	int				i;
	t_second_parse	*temp;

	temp = begin;
	i = 0;
	while (temp != NULL && temp->value != _PIPE)
	{
		if (temp->value == _R_OUTPUT || temp->value == _R_OUTPUT_2)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	find_nbr_in(t_second_parse *begin)
{
	int				i;
	t_second_parse	*temp;

	temp = begin;
	i = 0;
	while (temp != NULL && temp->value != _PIPE)
	{
		if (temp->value == _R_INPUT || temp->value == _R_INPUT_2
			|| temp->value == _DELIMITEUR_2)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	init_redirection(t_minishell *m, char *line, t_second_parse *begin)
{
	(void)line;
	m->r.i = 0;
	m->r.error = 0;
	m->r.fd_out_save = dup(STDOUT_FILENO);
	m->r.fd_in_save = dup(STDIN_FILENO);
	m->r.nbr_out = find_nbr_out(begin);
	m->r.nbr_in = find_nbr_in(begin);
}
