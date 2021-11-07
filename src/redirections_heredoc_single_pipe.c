/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc_single_pipe.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 01:26:59 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/06 22:37:50 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_input_heredoc_single(int i, t_minishell *m,
			t_second_parse *temp)
{
	char	*str;
	int		fd2;

	str = NULL;
	fd2 = open("/tmp/lala", O_CREAT | O_RDWR | O_TRUNC, 0777);
	m->s.fds[i] = open("/tmp/lala", O_RDWR);
	while (ft_strcmp(str, temp->str) == 1 && g_signal == 0)
	{
		str = ft_free_null(str);
		str = readline("Heredoc> ");
		if (ft_strcmp(str, temp->str) == 1)
			write_in_herdoc(str, fd2, m, temp->value);
	}
	str = ft_free_null(str);
	close(fd2);
	unlink("/tmp/lala");
}

void	write_heredoc_single(t_second_parse *temp, t_minishell *m)
{
	int	fd;
	int	i;

	fd = dup(STDIN_FILENO);
	i = 0;
	while (temp != NULL && g_signal == 0)
	{
		if (temp->value == _R_INPUT_2 || temp->value == _DELIMITEUR_2)
		{
			redirection_input_heredoc_single(i, m, temp);
			i++;
			m->s.j = i;
		}
		temp = temp->next;
	}
	if (g_signal != 0)
		 dup2(fd, STDIN_FILENO);
	close(fd);
}

void	init_and_write_in_heredoc_single(t_second_parse *begin, t_minishell *m)
{
	m->s.i = -1;
	m->s.j = -1;
	m->s.fds = NULL;
	m->s.nbr_h = find_nbr_heredoc(begin);
	if (m->s.nbr_h != 0)
		m->s.fds = malloc(sizeof(int) * m->s.nbr_h);
	if (m->s.nbr_h != 0)
		write_heredoc_single(begin, m);
}

// get_next_line_modif(STDIN_FILENO, &str);
