/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:55:52 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/26 05:28:19 by rkhelif          ###   ########.fr       */
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
		argv = argv_list_to_tab(begin);
	else
		argv = list_env_argv_to_tab(begin, m->e);
	if (argv == NULL)
		free_inside_process_without_pipe_2(argv, env, m, line);
	if (argv[0] != NULL)
		execve(argv[0], argv, env);
	free_inside_process_without_pipe_3(argv, env, m, line);
}

void	executing_without_pipe(t_second_parse *begin, t_minishell *m,
			char *line)
{
	t_second_parse	*temp;
	int				fd;
	pid_t			pid;

	fd = 1;
	(void)fd;
	temp = begin;
	while (temp != NULL && temp->value != EXP)
		temp = temp->next;
	if (temp == NULL)
		return ;
	if (is_it_a_built_in(temp->str) == 1)
		return (make_a_built_in(temp, m, line));
	pid = fork();
	if (pid < 0)
		return (error2(errno));
	if (pid == 0)
		child_process_whithout_pipe(temp, m, line);
	if (pid != 0)
		waitpid(pid, NULL, 0);
}

void	executing(t_second_parse *begin, t_minishell *m, char *line)
{
	t_second_parse	*temp;
	int				nbr_pipe;

	temp = begin;
	nbr_pipe = find_nbr_pipe(begin);
	if (nbr_pipe == 0)
		return (executing_without_pipe(begin, m, line));
	(void)temp;
}
