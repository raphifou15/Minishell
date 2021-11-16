/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_multipipes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:32:26 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 20:34:19 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirection_output_multipipe_1(t_second_parse *temp, t_minishell *m,
			char *line)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (m->r.fd_out < 0)
		free_child_1(m, line, errno);
	if (--m->r.nbr_out == 0)
	{
		if (dup2(m->r.fd_out, STDOUT_FILENO) < 0)
		{
			close(m->r.fd_out);
			free_child_1(m, line, errno);
		}
	}
	close(m->r.fd_out);
}

static void	redirection_output_multipipe_2(t_second_parse *temp, t_minishell *m,
			char *line)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (m->r.fd_out < 0)
		free_child_1(m, line, errno);
	if (--m->r.nbr_out == 0)
	{
		if (dup2(m->r.fd_out, STDOUT_FILENO) < 0)
		{
			close(m->r.fd_out);
			free_child_1(m, line, errno);
		}
	}
	close(m->r.fd_out);
}

static void	redirection_input_multipipe_1(t_second_parse *temp, t_minishell *m,
			char *line)
{
	m->r.fd_in = open(temp->str, O_RDONLY);
	if (m->r.fd_in < 0)
	{
		ft_putstr_err("\e[15;31m");
		ft_putstr_err(temp->str);
		ft_putstr_err(": \e[0m");
		error2(errno);
		m->r.i = 1;
	}
	else
	{
		if (--m->r.nbr_in == 0)
		{
			if (dup2(m->r.fd_in, STDIN_FILENO) < 0)
			{
				close(m->r.fd_in);
				free_child_1(m, line, errno);
			}
		}
		close(m->r.fd_in);
	}
}

static void	redirection_input_multipipe_2(t_second_parse *temp, t_minishell *m,
			char *line)
{
	(void)temp;
	m->mp.i++;
	if (--m->r.nbr_in == 0)
	{
		if (dup2(m->mp.fds[m->mp.i], STDIN_FILENO) < 0)
			free_child_1(m, line, errno);
	}
}

void	redirections_multipipes(t_second_parse *temp, t_minishell *m,
			char *line)
{
	if (m->r.i == 0 && temp->value == _R_OUTPUT)
		redirection_output_multipipe_1(temp, m, line);
	if (m->r.i == 0 && temp->value == _R_OUTPUT_2)
		redirection_output_multipipe_2(temp, m, line);
	if (m->r.i == 0 && temp->value == _R_INPUT)
		redirection_input_multipipe_1(temp, m, line);
	if (m->r.i == 0 && (temp->value == _R_INPUT_2
			|| temp->value == _DELIMITEUR_2))
		redirection_input_multipipe_2(temp, m, line);
}
