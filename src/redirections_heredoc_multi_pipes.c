/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc_multi_pipes.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 00:02:54 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/12 21:19:25 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirection_input_heredoc(int i, t_minishell *m,
				t_second_parse *temp)
{
	char	*str;
	int		fd2;

	str = NULL;
	fd2 = open("/tmp/lala", O_CREAT | O_RDWR | O_TRUNC, 0777);
	m->mp.fds[i] = open("/tmp/lala", O_RDWR);
	while (ft_strcmp(str, temp->str) == 1 && g_signal == 0)
	{
		str = ft_free_null(str);
		str = readline("Heredoc> ");
		if (str == NULL)
		{
			 write(0, "\n", 1);
			 break ;
		}
		if (ft_strcmp(str, temp->str) == 1)
			write_in_herdoc(str, fd2, m, temp->value);
	}
	str = ft_free_null(str);
	close(fd2);
	unlink("/tmp/lala");
}

static void	write_heredoc2(t_second_parse *temp, t_minishell *m)
{
	int	i;
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd < 0)
	{
		error2(errno);
		m->retour = 1;
		free(m->mp.fds);
		return ;
	}
	i = 0;
	while (temp != NULL && g_signal == 0)
	{
		if (temp->value == _R_INPUT_2 || temp->value == _DELIMITEUR_2)
		{
			redirection_input_heredoc(i, m, temp);
			i++;
			m->mp.j = i;
		}
		temp = temp->next;
	}
	if (g_signal != 0)
		 dup2(fd, STDIN_FILENO);
	close(fd);
}

int	find_nbr_heredoc(t_second_parse *temp)
{
	int	i;

	i = 0;
	while (temp != NULL)
	{
		if (temp->value == _R_INPUT_2 || temp->value == _DELIMITEUR_2)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	init_heredoc_and_write_in_file(t_second_parse *begin, t_minishell *m,
			int nbr_pipe)
{
	m->mp.nbr_p = nbr_pipe;
	m->mp.i = -1;
	m->mp.j = -1;
	m->mp.fds = NULL;
	m->mp.nbr_h = find_nbr_heredoc(begin);
	if (m->mp.nbr_h != 0)
	{
		m->mp.fds = malloc(sizeof(int) * m->mp.nbr_h);
		if (m->mp.fds == NULL)
		{
			error1(0);
			m->retour = 1;
			return ;
		}
	}
	if (m->mp.nbr_h != 0)
		write_heredoc2(begin, m);
}

// write(2, "Heredoc> ", 9);
// get_next_line_modif(STDIN_FILENO, &str);
