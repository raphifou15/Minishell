/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_inside_pipe_multi.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:29:26 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/13 19:21:24 by rkhelif          ###   ########.fr       */
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
	free(m->mp.pid);
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
	if (argv[0] != NULL)
		error3(argv[0]);
	ft_free_double_tab(argv);
	ft_free_double_tab(env);
	destroy_all(m, line, m->use);
	ft_free_all_elem_env(m->e);
	free(m->mp.fds);
	m->mp.fds = NULL;
	free(m->mp.pid);
	close(2);
	close(1);
	close(0);
	exit(127);
}

void	free_child_1(t_minishell *m, char *line, int err)
{
	int	j;

	j = -1;
	error2(err);
	close(m->mp.pipefd[0]);
	close(m->mp.pipefd[1]);
	close(m->mp.fd_in);
	while (++j < m->mp.nbr_h)
		close(m->mp.fds[j]);
	free(m->mp.fds);
	m->mp.fds = NULL;
	free(m->mp.pid);
	destroy_all(m, line, m->use);
	ft_free_all_elem_env(m->e);
	close(2);
	close(1);
	close(0);
	exit(1);
}
