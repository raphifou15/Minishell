/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:55:52 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/15 04:07:41 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_nbr_pipe(t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;

	i = 0;
	temp = begin;
	while (temp != NULL)
	{
		if (temp->value == _PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	child_process_whithout_pipe(t_second_parse *begin, t_minishell *m,
			char *line)
{
	char	**env;
	char	**argv;

	env = NULL;
	env = env_list_to_tab(m->e);
	if (env == NULL)
		free_inside_process_without_pipe_1(env, m, line);
	if (absolute_way(begin) == 1)
		argv = argv_list_to_tab(begin, 0);
	else
		argv = list_env_argv_to_tab(begin, m->e);
	if (argv == NULL)
		free_inside_process_without_pipe_2(argv, env, m, line);
	close(m->r.fd_out_save);
	if (argv[0] != NULL)
		execve(argv[0], argv, env);
	if (errno != 13)
		return (free_inside_process_without_pipe_3(argv, env, m, line));
	free(line);
	free_inside_process_without_pipe_4(argv, env, m, errno);
}

void	executing_without_pipe(t_second_parse *begin, t_minishell *m,
			char *line)
{
	t_second_parse	*temp;
	pid_t			pid;

	temp = begin;
	signal_heredoc();
	temp = redirections(begin, m, line);
	if (temp == NULL || m->r.error == 1 || g_signal != 0)
	{
		free(m->s.fds);
		return ;
	}
	if (is_it_a_built_in(temp->str) == 1)
		return (make_a_built_in(temp, m, line));
	pid = fork();
	if (pid < 0)
	{
		m->retour = 1;
		return (error2(errno));
	}
	signal_child();
	if (pid == 0)
		child_process_whithout_pipe(temp, m, line);
	if (pid != 0)
		wait_without_pipe(m, pid);
	m->s.fds = ft_free3(m->s.fds);
}

void	executing(t_second_parse *begin, t_minishell *m, char *line)
{
	int				nbr_pipe;

	nbr_pipe = find_nbr_pipe(begin);
	m->mp.nbr_p = nbr_pipe;
	if (nbr_pipe == 0)
		return (executing_without_pipe(begin, m, line));
	m->use = 2;
	executing_with_pipe(begin, m, line, nbr_pipe);
}

// chercher si tout les retours des fonctions ne provoque pas de leaks ou de
// segfault;

// executing_without_pipe.
