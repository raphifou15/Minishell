/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 00:52:00 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/11 22:06:36 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirection_output(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (--m->r.nbr_out == 0)
		dup2(m->r.fd_out, STDOUT_FILENO);
	close(m->r.fd_out);
}

static void	redirection_output2(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (--m->r.nbr_out == 0)
		dup2(m->r.fd_out, STDOUT_FILENO);
	close(m->r.fd_out);
}

static void	redirection_input(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_in = open(temp->str, O_RDONLY | O_APPEND, 0777);
	if (m->r.fd_in < 0)
		m->r.i = 1;
	else
	{
		if (--m->r.nbr_in == 0)
			dup2(m->r.fd_in, STDIN_FILENO);
		close(m->r.fd_in);
	}
}

static void	redirection_input2(t_minishell *m, t_second_parse *temp)
{
	(void)temp;
	m->s.i++;
	if (--m->r.nbr_in == 0)
		dup2(m->s.fds[m->s.i], STDIN_FILENO);
}

t_second_parse	*redirections(t_second_parse *begin, t_minishell *m, char *line)
{
	t_second_parse	*temp;

	init_and_write_in_heredoc_single(begin, m);
	if (m->s.nbr_h != 0 && m->s.fds == NULL)
		return (begin);
	init_redirection(m, line, begin);
	temp = begin;
	while (temp != NULL && temp->value != EXP && g_signal == 0)
	{
		if (m->r.i == 0 && temp->value == _R_OUTPUT)
			redirection_output(m, temp);
		if (m->r.i == 0 && temp->value == _R_OUTPUT_2)
			redirection_output2(m, temp);
		if (m->r.i == 0 && temp->value == _R_INPUT)
			redirection_input(m, temp);
		if (temp->value == _R_INPUT_2 || temp->value == _DELIMITEUR_2)
			redirection_input2(m, temp);
		temp = temp->next;
	}
	close_fds_and_error(m);
	return (temp);
}

//securiser toutes les fontions du au redirection faire ATTENTION que tout soi
//bien securiser;
