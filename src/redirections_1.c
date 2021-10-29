/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 00:52:00 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/29 03:46:48 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_output(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (--m->r.nbr_out == 0)
		dup2(m->r.fd_out, STDOUT_FILENO);
	close(m->r.fd_out);
}

void	redirection_output2(t_minishell *m, t_second_parse *temp)
{
	m->r.fd_out = open(temp->str, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (--m->r.nbr_out == 0)
		dup2(m->r.fd_out, STDOUT_FILENO);
	close(m->r.fd_out);
}

void	redirection_input(t_minishell *m, t_second_parse *temp)
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

void	redirection_input2(t_minishell *m, t_second_parse *temp)
{
	char	*str;
	int		fd2;

	str = NULL;
	--m->r.nbr_in;
	fd2 = open("/tmp/lala", O_CREAT | O_RDWR | O_TRUNC, 0777);
	m->r.fd_in = open("/tmp/lala", O_RDWR);
	while (ft_strcmp(str, temp->str) == 1)
	{
		write(1, "Heredoc> ", 9);
		str = ft_free_null(str);
		get_next_line_modif(STDIN_FILENO, &str);
		if (m->r.nbr_in == 0 && ft_strcmp(str, temp->str) == 1)
		{
			ft_putstr_fd(str, fd2);
			ft_putstr_fd("\n", fd2);
		}
	}
	str = ft_free_null(str);
	close(fd2);
	unlink("/tmp/lala");
	if (m->r.nbr_in == 0)
		dup2(m->r.fd_in, STDIN_FILENO);
	close(m->r.fd_in);
}

t_second_parse	*redirections(t_second_parse *begin, t_minishell *m, char *line)
{
	t_second_parse	*temp;

	init_redirection(m, line, begin);
	temp = begin;
	while (temp != NULL && temp->value != EXP)
	{
		if (m->r.i == 0 && temp->value == _R_OUTPUT)
			redirection_output(m, temp);
		if (m->r.i == 0 && temp->value == _R_OUTPUT_2)
			redirection_output2(m, temp);
		if (m->r.i == 0 && temp->value == _R_INPUT)
			redirection_input(m, temp);
		if (temp->value == _R_INPUT_2)
			redirection_input2(m, temp);
		temp = temp->next;
	}
	if (m->r.i != 0)
	{
		ft_putstr_err("m->r.fd_in error a changer apres \n");
		m->r.error = 1;
	}
	return (temp);
}

//securiser toutes les fontions du au redirection faire ATTENTION que tout soi
//bien securiser;
