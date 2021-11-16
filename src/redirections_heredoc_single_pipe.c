/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc_single_pipe.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 01:26:59 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 20:36:18 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	good_close_dup_fail(t_minishell *m, int err)
{
	m->use = 3;
	error2(err);
	return ;
}

static void	good_close_if_fd_fail(t_minishell *m, int i, int err)
{
	while (i > 0)
		close(m->s.fds[--i]);
	error2(err);
	m->use = 3;
}

static void	redirection_input_heredoc_single(int i, t_minishell *m,
			t_second_parse *temp, char *str)
{
	int		fd2;

	fd2 = open("/tmp/lala", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
		return (good_close_if_fd_fail(m, i, errno));
	m->s.fds[i] = open("/tmp/lala", O_RDWR);
	if (m->s.fds[i] < 0)
	{
		close(fd2);
		return (good_close_if_fd_fail(m, i, errno));
	}
	while (ft_strcmp(str, temp->str) == 1 && g_signal == 0)
	{
		str = ft_free_null(str);
		str = readline("Heredoc> ");
		if (str == NULL)
			write(0, "\n", 1);
		if (str == NULL)
			break ;
		if (ft_strcmp(str, temp->str) == 1)
			write_in_herdoc(str, fd2, m, temp->value);
	}
	str = ft_free_null(str);
	close(fd2);
	unlink("/tmp/lala");
}

static void	write_heredoc_single(t_second_parse *temp, t_minishell *m, int fd,
				int i)
{
	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (good_close_dup_fail(m, errno));
	while (temp != NULL && g_signal == 0)
	{
		if (temp->value == _R_INPUT_2 || temp->value == _DELIMITEUR_2)
		{
			redirection_input_heredoc_single(i, m, temp, NULL);
			if (m->use == 3)
			{
				if (dup2(fd, STDIN_FILENO) == -1)
					error2(errno);
				close(fd);
				return ;
			}
			i++;
			m->s.j = i;
		}
		temp = temp->next;
	}
	if (g_signal != 0 && dup2(fd, STDIN_FILENO) == -1)
		error2(errno);
	close(fd);
}

void	init_and_write_in_heredoc_single(t_second_parse *begin, t_minishell *m)
{
	m->s.i = -1;
	m->s.j = -1;
	m->s.fds = NULL;
	m->s.nbr_h = find_nbr_heredoc(begin);
	if (m->s.nbr_h != 0)
	{
		m->s.fds = malloc(sizeof(int) * m->s.nbr_h);
		if (m->s.fds == NULL)
		{
			error1(0);
			m->r.error = 1;
			m->use = 3;
			m->retour = 1;
		}
	}
	if (m->s.nbr_h != 0 && m->s.fds != NULL)
	{
		write_heredoc_single(begin, m, 0, 0);
		if (m->use == 3)
		{
			m->s.fds = ft_free3(m->s.fds);
			m->r.error = 1;
			m->retour = 1;
		}
	}
}

// get_next_line_modif(STDIN_FILENO, &str);
