/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 23:27:32 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/12 17:57:10 by rkhelif          ###   ########.fr       */
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
		redirections_multipipes(temp, m);
		temp = temp->next;
	}
	(void)line;
	return (temp);
}

static void	executing_inside_child_multi_pipe_next(t_minishell *m, char *line,
			char **env, char **argv)
{
	int	j;

	j = -1;
	close(m->mp.pipefd[0]);
	close(m->mp.pipefd[1]);
	close(m->mp.fd_in);
	while (++j < m->mp.nbr_h)
		close(m->mp.fds[j]);
	if (argv[0] != NULL)
		execve(argv[0], argv, env);
	free_child_proc_mult_end(m, line, env, argv);
}

static void	executing_inside_child_multi_pipe(t_second_parse *temp,
			t_minishell *m, int i, char *line)
{
	char	**argv;
	char	**env;

	argv = NULL;
	env = NULL;
	if (i != 0)
		dup2(m->mp.fd_in, STDIN_FILENO);
	if (i != m->mp.nbr_p)
		dup2(m->mp.pipefd[1], STDOUT_FILENO);
	temp = redirection_multiple_pipe(temp, m, line);
	if (temp == NULL || m->r.i == 1)
		free_child_proc_mult_doc_fail(m, line);
	env = env_list_to_tab(m->e);
	if (absolute_way(temp) == 1)
		argv = argv_list_to_tab(temp, 0);
	else
		argv = list_env_argv_to_tab(temp, m->e);
	executing_inside_child_multi_pipe_next(m, line, env, argv);
}

void	executing_with_pipe(t_second_parse *begin, t_minishell *m, char *line,
			int nbr_pipe)
{
	t_second_parse	*temp;
	int				i;

	i = 0;
	temp = begin;
	m->mp.fd_in = dup(STDIN_FILENO);
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	init_heredoc_and_write_in_file(begin, m, nbr_pipe);
	signal(SIGINT, handler_inside_child);
	signal(SIGQUIT, handler_inside_child);
	while (i <= nbr_pipe && g_signal == 0)
	{
		pipe(m->mp.pipefd);
		m->mp.pid = fork();
		if (m->mp.pid == 0)
			executing_inside_child_multi_pipe(temp, m, i, line);
		temp = inside_parent_multi_pipe(temp, m);
		i++;
	}
	reboot_executing_with_pipe(m);
}
