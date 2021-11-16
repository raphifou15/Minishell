/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_inside_pipe_multi.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:29:26 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 01:24:32 by rkhelif          ###   ########.fr       */
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
	exit(1);
}

void	free_child_proc_mult_end(t_minishell *m, char *line, char **env,
			char **argv)
{
	if (argv[0] != NULL)
	{
		if (argv[0][0] == '\0')
			ft_putstr_err("\e[15;31mCommand '' not found\e[0m\n");
		else
			error3(argv[0]);
	}
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

void	free_child_2(t_minishell *m, char *line)
{
	int	j;

	j = -1;
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
}

void	free_child_proc_mult_end2(t_minishell *m, char *line, int err,
			char **argv)
{
	int	a;

	ft_putstr("\e[15;31m");
	ft_putstr(argv[0]);
	ft_putstr(":  \e[0m");
	if (ft_strcmp(argv[0], ".") == 0 && argv[1] == NULL)
		ft_putstr("\e[15;31mfilename argument required\n\e[0m");
	else
		error2(err);
	if (ft_strcmp(argv[0], ".") == 0 && argv[1] == NULL)
		a = 2;
	else
		a = 126;
	error2(err);
	ft_free_double_tab(argv);
	destroy_all(m, line, m->use);
	ft_free_all_elem_env(m->e);
	free(m->mp.fds);
	m->mp.fds = NULL;
	free(m->mp.pid);
	close(2);
	close(1);
	close(0);
	exit(a);
}
