/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_3_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:04:01 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/10 19:57:21 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_list_is_ordered(t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;
	int				elem;

	elem = 0;
	temp = begin;
	i = 0;
	while (temp != NULL)
	{
		if (temp->value == EXP)
			i = 1;
		if (temp->value == _PIPE)
			i = 0;
		if (i != 0 && (temp->value != _PIPE && temp->value != EXP))
			return (elem);
		elem++;
		temp = temp->next;
	}
	return (0);
}

t_second_parse	*change_place_elem(t_second_parse *begin, t_minishell *m,
					int elem, int i)
{
	t_second_parse	*temp;
	t_second_parse	*temp2;
	t_second_parse	*temp3;
	t_second_parse	*temp4;

	temp = begin;
	if (elem == 1)
	{	
		temp2 = temp->next->next;
		begin = temp->next;
		m->p3 = begin;
		begin->next = temp;
		temp->next = temp2;
		return (begin);
	}
	while (++i < elem - 2)
		temp = temp->next;
	temp2 = temp->next;
	temp3 = temp->next->next;
	temp4 = temp->next->next->next;
	temp->next = temp3;
	temp3->next = temp2;
	temp2->next = temp4;
	return (begin);
}

void	order_list(t_second_parse *begin, t_minishell *m)
{
	int				elem;

	elem = 0;
	elem = check_if_list_is_ordered(begin);
	while (elem != 0)
	{
		begin = change_place_elem(begin, m, elem, -1);
		elem = check_if_list_is_ordered(begin);
	}
}

int	check_syntax_error_pipe(t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;

	i = 0;
	temp = begin;
	while (temp != NULL)
	{
		if (i == 0 && temp->value == _PIPE)
			return (error1(7) + 1);
		if (temp->value == _PIPE && temp->next == NULL)
			return (error1(7) + 1);
		i++;
		temp = temp->next;
	}
	return (0);
}

void	corrige_empty_quote(t_second_parse *temp)
{
	int	i;

	while (temp != NULL)
	{
		i = -1;
		if (temp->value == _QUOTE_EMPTY)
		{
			temp->value = EXP;
			while (temp->str[++i] != '\0')
				temp->str[i] = '\0';
		}
		temp = temp->next;
	}
}

//retourner une erreur si un pipe est en premiere position
//retourner une erreur si il n'y a rien apres un pipe;
