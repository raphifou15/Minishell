/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_multipipes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:32:26 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/06 23:22:27 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_output_multipipe_1(t_second_parse *temp, t_minishell *m)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (--m->r.nbr_out == 0)
		dup2(m->r.fd_out, STDOUT_FILENO);
	close(m->r.fd_out);
}

void	redirection_output_multipipe_2(t_second_parse *temp, t_minishell *m)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (--m->r.nbr_out == 0)
		dup2(m->r.fd_out, STDOUT_FILENO);
	close(m->r.fd_out);
}

void	redirection_input_multipipe_1(t_second_parse *temp, t_minishell *m)
{
	m->r.fd_in = open(temp->str, O_RDONLY);
	if (m->r.fd_in < 0)
	{
		ft_putstr_err("error fd doesn't exist \n");
		m->r.i = 1;
	}
	else
	{
		if (--m->r.nbr_in == 0)
			dup2(m->r.fd_in, STDIN_FILENO);
		close(m->r.fd_in);
	}
}

void	redirection_input_multipipe_2(t_second_parse *temp, t_minishell *m)
{
	(void)temp;
	m->mp.i++;
	if (--m->r.nbr_in == 0)
		dup2(m->mp.fds[m->mp.i], STDIN_FILENO);
}

void	redirections_multipipes(t_second_parse *temp, t_minishell *m)
{
	if (m->r.i == 0 && temp->value == _R_OUTPUT)
		redirection_output_multipipe_1(temp, m);
	if (m->r.i == 0 && temp->value == _R_OUTPUT_2)
		redirection_output_multipipe_2(temp, m);
	if (m->r.i == 0 && temp->value == _R_INPUT)
		redirection_input_multipipe_1(temp, m);
	if (m->r.i == 0 && (temp->value == _R_INPUT_2
			|| temp->value == _DELIMITEUR_2))
		redirection_input_multipipe_2(temp, m);
}
