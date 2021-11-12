/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_inside_process_wihout_pipe.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 04:37:21 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/12 17:35:50 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_inside_process_without_pipe_1(char **env, t_minishell *m,
			char *line)
{
	error1(0);
	close(m->r.fd_out_save);
	close(m->r.fd_in_save);
	ft_free_double_tab(env);
	ft_free_all_the_list_2(m->p3);
	ft_free_all_elem_env(m->e);
	ft_free(line);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_inside_process_without_pipe_2(char **argv, char **env,
			t_minishell *m, char *line)
{
	error1(0);
	close(m->r.fd_out_save);
	close(m->r.fd_in_save);
	ft_free_double_tab(argv);
	ft_free_double_tab(env);
	ft_free_all_the_list_2(m->p3);
	ft_free_all_elem_env(m->e);
	ft_free(line);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_inside_process_without_pipe_3(char **argv, char **env,
			t_minishell *m, char *line)
{
	if (argv[0] != NULL)
		error1(5);
	close(m->r.fd_out_save);
	close(m->r.fd_in_save);
	free(m->s.fds);
	m->s.fds = NULL;
	close(0);
	close(1);
	close(2);
	ft_free_double_tab(argv);
	ft_free_double_tab(env);
	ft_free_all_the_list_2(m->p3);
	ft_free_all_elem_env(m->e);
	ft_free(line);
	exit(127);
}
