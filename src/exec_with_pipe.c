/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 23:27:32 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/15 05:25:18 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_redirection2(t_minishell *m, t_second_parse *begin)
{
	m->r.i = 0;
	m->r.error = 0;
	m->r.nbr_out = find_nbr_out(begin);
	m->r.nbr_in = find_nbr_in(begin);
}

static t_second_parse	*redirection_multiple_pipe(t_second_parse *begin,
					t_minishell *m, char *line)
{
	t_second_parse	*temp;

	temp = begin;
	init_redirection2(m, temp);
	while (temp != NULL && temp->value != EXP)
	{
		redirections_multipipes(temp, m, line);
		temp = temp->next;
	}
	(void)line;
	return (temp);
}

static void	executing_inside_child_multi_pipe_next(t_minishell *m, char *line,
			char **env, char **argv)
{
	int	j;

	if (argv == NULL)
	{
		ft_free_double_tab(env);
		free_child_1(m, line, errno);
	}
	j = -1;
	close(m->mp.pipefd[0]);
	close(m->mp.pipefd[1]);
	close(m->mp.fd_in);
	while (++j < m->mp.nbr_h)
		close(m->mp.fds[j]);
	if (argv[0] != NULL)
		execve(argv[0], argv, env);
	if (errno != 13)
		return (free_child_proc_mult_end(m, line, env, argv));
	ft_free_double_tab(env);
	free_child_proc_mult_end2(m, line, errno, argv);
}

void	executing_inside_child_multi_pipe(t_second_parse *temp,
			t_minishell *m, int i, char *line)
{
	char	**argv;
	char	**env;

	argv = NULL;
	env = NULL;
	if (i != 0)
	{
		if (dup2(m->mp.fd_in, STDIN_FILENO) < 0)
			free_child_1(m, line, errno);
	}
	if (i != m->mp.nbr_p)
	{
		if (dup2(m->mp.pipefd[1], STDOUT_FILENO) < 0)
			free_child_1(m, line, errno);
	}
	temp = redirection_multiple_pipe(temp, m, line);
	if (temp == NULL || m->r.i == 1)
		free_child_proc_mult_doc_fail(m, line);
	if (is_it_a_built_in(temp->str) == 1)
		make_a_built_in_pipe(m, temp, line);
	env = env_list_to_tab(m->e);
	if (env == NULL)
		free_child_1(m, line, errno);
	argv = argv_inside_multi_pipe_norme(temp, m, argv);
	executing_inside_child_multi_pipe_next(m, line, env, argv);
}

void	executing_with_pipe(t_second_parse *begin, t_minishell *m, char *line,
			int nbr_pipe)
{
	t_second_parse	*temp;

	temp = begin;
	m->mp.fd_in = dup(STDIN_FILENO);
	if (m->mp.fd_in < 0)
		return (good_return_multipipe_1(m, errno, 0));
	signal_heredoc();
	m->mp.pid = malloc(sizeof(pid_t) * (nbr_pipe + 1));
	if (m->mp.pid == NULL)
		return (good_return_multipipe_1(m, errno, 2));
	init_heredoc_and_write_in_file(begin, m, nbr_pipe);
	if (m->retour != 0 || g_signal != 0)
		return (good_return_multipipe_1(m, errno, 1));
	signal_child();
	return (boucle_pipe_fork(nbr_pipe, m, temp, line));
}
