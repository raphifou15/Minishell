/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:42:47 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/10 19:57:28 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_next_value(t_second_parse *begin, int v)
{
	t_second_parse	*temp;

	temp = begin;
	if (temp->next != NULL)
		temp = temp->next;
	temp->value = v;
}

void	delete_elem_inside_list(t_second_parse *begin, int be)
{
	int				i;
	t_second_parse	*temp;
	t_second_parse	*temp2;

	temp = begin;
	i = 0;
	if (i > be)
	{
		ft_free(temp->str);
		ft_free2(temp);
		return ;
	}
	while (temp != NULL && i < be)
	{
		i++;
		temp = temp->next;
	}
	temp2 = temp;
	temp = temp->next;
	temp2->next = temp->next;
	ft_free(temp->str);
	ft_free2(temp);
}

int	redirection(int value)
{
	if (value == _R_INPUT || value == _R_OUTPUT
		|| value == _R_INPUT_2 || value == _R_OUTPUT_2
		|| value == _DELIMITEUR_2)
		return (1);
	return (0);
}

void	corrige_redirection(t_second_parse *begin, t_minishell *m)
{
	t_second_parse	*temp;
	int				i;

	i = 0;
	temp = begin;
	while (temp != NULL)
	{
		if (redirection(temp->value) == 1)
		{	
			change_next_value(temp, temp->value);
			temp = temp->next;
			delete_elem_inside_list(begin, i - 1);
			if (i == 0)
			{
				begin = temp;
				m->p3 = begin;
			}
		}
		i++;
		temp = temp->next;
	}
}

int	check_error_syntax(t_second_parse *begin)
{
	t_second_parse	*temp;

	temp = begin;
	while (temp != NULL)
	{
		if (redirection(temp->value) == 1)
		{
			temp = temp->next;
			if (temp == NULL)
				return (error1(4) + 1);
			if (temp->value != EXP && temp->value != _DELIMITEUR)
				return (error1(4) + 1);
		}
		else
			temp = temp->next;
	}
	return (0);
}
