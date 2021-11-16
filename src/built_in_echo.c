/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:20:46 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 18:21:01 by alebross         ###   ########.fr       */
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
