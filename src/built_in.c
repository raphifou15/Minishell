/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 04:55:58 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 18:52:01 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_a_built_in_pipe(t_minishell *m, t_second_parse *temp, char *line)
{
	make_a_built_in(temp, m, line);
	free_child_2(m, line);
	exit(m->retour);
}

int	is_it_a_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	make_a_built_in(t_second_parse *begin, t_minishell *m, char *line)
{
	m->retour = 0;
	if (ft_strcmp(begin->str, "echo") == 0)
		return (built_in_echo(m, begin));
	if (ft_strcmp(begin->str, "env") == 0)
		return (built_in_env(m->e));
	if (ft_strcmp(begin->str, "pwd") == 0)
		return (built_in_pwd(m));
	if (ft_strcmp(begin->str, "unset") == 0)
		return (built_in_unset(m->e, m, begin->next, 0));
	if (ft_strcmp(begin->str, "cd") == 0)
		return (built_in_cd(m, begin));
	if (ft_strcmp(begin->str, "export") == 0)
		return (built_in_export(m, begin, 0));
	if (ft_strcmp(begin->str, "exit") == 0)
	{
		if (m->mp.nbr_p <= 0)
			return (built_in_exit(m, begin, line));
		else
			(built_in_exit2(m, begin, line));
	}
}
