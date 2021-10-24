/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:55:52 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/24 06:08:44 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_whithout_pipe(t_second_parse *begin, t_minishell *m,
			char *line)
{
	char	**env;

	env = env_list_to_tab(m->e);
	ft_free_all_the_list_2(m->p3);
	ft_free_all_elem_env(m->e);
	ft_free(line);
	(void)begin;
	(void)env;
	exit(EXIT_SUCCESS);
}

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
	pid = fork();
	if (pid < 0)
		return (error2(errno));
	if (pid == 0)
		child_process_whithout_pipe(temp, m, line);
	printf("start executing here\n");
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

//Tram de l'histoire 
//changer le env liste chaine en tab **
