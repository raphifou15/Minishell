/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 00:52:00 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 20:35:08 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	output(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (m->r.fd_out < 0)
	{
		error2(errno);
		m->retour = 1;
		m->r.error = 1;
		close_fds_and_error(m);
		return (-1);
	}
	if (--m->r.nbr_out == 0)
	{
		if (dup2(m->r.fd_out, STDOUT_FILENO) == -1)
		{
			error2(errno);
			m->retour = 1;
			m->r.error = 1;
			close(m->r.fd_out);
			close_fds_and_error(m);
			return (-1);
		}
	}
	close(m->r.fd_out);
	return (0);
}

static int	output2(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (m->r.fd_out < 0)
	{
		error2(errno);
		m->retour = 1;
		m->r.error = 1;
		close_fds_and_error(m);
		return (-1);
	}
	if (--m->r.nbr_out == 0)
	{
		if (dup2(m->r.fd_out, STDOUT_FILENO) == -1)
		{
			error2(errno);
			m->retour = 1;
			m->r.error = 1;
			close(m->r.fd_out);
			close_fds_and_error(m);
			return (-1);
		}
	}
	close(m->r.fd_out);
	return (0);
}

static int	input(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_in = open(temp->str, O_RDONLY | O_APPEND, 0644);
	if (m->r.fd_in < 0)
	{
		m->r.i = 1;
		m->retour = 1;
		error2(errno);
	}
	else
	{
		if (--m->r.nbr_in == 0)
		{
			if (dup2(m->r.fd_in, STDIN_FILENO) == -1)
			{
				error2(errno);
				m->r.error = 1;
				m->retour = 1;
				close(m->r.fd_in);
				close_fds_and_error(m);
				return (-1);
			}
		}
		close(m->r.fd_in);
	}
	return (0);
}

static int	input2(t_minishell *m, t_second_parse *temp)
{
	(void)temp;
	m->s.i++;
	if (--m->r.nbr_in == 0)
	{
		if (dup2(m->s.fds[m->s.i], STDIN_FILENO) == -1)
		{
			error2(errno);
			m->r.error = 1;
			m->retour = 1;
			close_fds_and_error(m);
			return (-1);
		}
	}
	return (0);
}

t_second_parse	*redirections(t_second_parse *begin, t_minishell *m, char *line)
{
	t_second_parse	*temp;

	temp = begin;
	init_and_write_in_heredoc_single(begin, m);
	if (m->s.nbr_h != 0 && m->s.fds == NULL)
		return (begin);
	if (init_redirection(m, line, begin) == -1)
		return (begin);
	while (temp != NULL && temp->value != EXP && g_signal == 0)
	{
		if (m->r.i == 0 && temp->value == _R_OUTPUT && output(m, temp) == -1)
			return (begin);
		if (m->r.i == 0 && temp->value == _R_OUTPUT_2 && output2(m, temp) == -1)
			return (begin);
		if (m->r.i == 0 && temp->value == _R_INPUT && input(m, temp) == -1)
			return (begin);
		if ((temp->value == _R_INPUT_2 || temp->value == _DELIMITEUR_2)
			&& (input2(m, temp) == -1))
			return (begin);
		temp = temp->next;
	}
	close_fds_and_error(m);
	return (temp);
}

//securiser toutes les fontions du au redirection faire ATTENTION que tout soi
//bien securiser;
