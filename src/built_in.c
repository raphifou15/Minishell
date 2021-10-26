/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 04:55:58 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/26 05:28:23 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_elem_echo(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
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

void	built_in_echo(t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;
	int				j;

	i = -1;
	temp = begin->next;
	j = check_first_elem_echo(temp->str);
	if (j == 1)
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

int	is_it_a_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	return (0);
}

void	make_a_built_in(t_second_parse *begin, t_minishell *m, char *line)
{
	if (ft_strcmp(begin->str, "echo") == 0)
		return (built_in_echo(begin));
	(void)m;
	(void)line;
}
