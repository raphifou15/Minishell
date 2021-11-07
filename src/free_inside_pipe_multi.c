/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_inside_pipe_multi.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:29:26 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/07 23:54:58 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_proc_mult_doc_fail(t_minishell *m, char *line)
{
	int	j;

	j = -1;
	close(m->mp.pipefd[0]);
	close(m->mp.pipefd[1]);
	close(m->mp.fd_in);
	while (++j < m->mp.nbr_h)
		close(m->mp.fds[j]);
	destroy_all(m, line, m->use);
	ft_free_all_elem_env(m->e);
	free(m->mp.fds);
	m->mp.fds = NULL;
	close(2);
	close(1);
	close(0);
	exit(0);
}

void	free_child_proc_mult_end(t_minishell *m, char *line, char **env,
			char **argv)
{
	ft_free_double_tab(argv);
	ft_free_double_tab(env);
	destroy_all(m, line, m->use);
	ft_free_all_elem_env(m->e);
	free(m->mp.fds);
	m->mp.fds = NULL;
	close(2);
	close(1);
	close(0);
	exit(0);
}
