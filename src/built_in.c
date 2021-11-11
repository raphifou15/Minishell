/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 04:55:58 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/10 20:15:11 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_elem_echo(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return (0);
	if (str[i + 1] == '\0')
		return (0);
	while (str[++i] != '\0')
	{
		if (i == 0 && str[i] != '-')
			return (0);
		if (i > 0 && str[i] != 'n')
			return (0);
	}
	return (1);
}

void	built_in_echo(t_minishell *m, t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;
	int				j;

	m->retour = 0;
	i = -1;
	temp = begin->next;
	if (temp == NULL)
		return (ft_putstr("\n"));
	j = check_first_elem_echo(temp->str);
	if (j == 1)
		temp = temp->next;
	while (temp != NULL && check_first_elem_echo(temp->str) == 1)
		temp = temp->next;
	while (temp != NULL && ++i != -1)
	{
		if (i != 0)
			ft_putstr(" ");
		ft_putstr(temp->str);
		temp = temp->next;
	}
	if (j != 1)
		ft_putstr("\n");
}

void	built_in_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (temp->ctn != NULL)
		{
			ft_putstr(temp->name);
			ft_putstr("=");
			ft_putstr(temp->ctn);
			ft_putstr("\n");
		}
		temp = temp->next;
	}
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
	if (ft_strcmp(begin->str, "echo") == 0)
		return (built_in_echo(m, begin));
	if (ft_strcmp(begin->str, "env") == 0)
		return (built_in_env(m->e));
	if (ft_strcmp(begin->str, "pwd") == 0)
		return (built_in_pwd());
	if (ft_strcmp(begin->str, "unset") == 0)
		return (built_in_unset(m->e, m, begin, 0));
	if (ft_strcmp(begin->str, "cd") == 0)
		return (built_in_cd(m, begin));
	if (ft_strcmp(begin->str, "export") == 0)
		return (built_in_export(m, begin, 0));
	if (ft_strcmp(begin->str, "exit") == 0)
		return (built_in_exit(m, begin, line));
}
