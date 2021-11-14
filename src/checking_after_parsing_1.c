/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <alebross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:56:01 by alebross          #+#    #+#             */
/*   Updated: 2021/11/14 21:23:25 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transform_value_for_dollar_inside_double_quote(t_first_parse **begin,
			int pivot)
{
	t_first_parse	*temp;
	int				pivot2;

	temp = *begin;
	pivot2 = 0;
	while (temp != NULL)
	{
		if (temp->value == _DOUBLE_QUOTE)
		{
			if (pivot == 0)
				pivot = 1;
			else
			{
				pivot = 0;
				pivot2 = 0;
			}
		}
		if (pivot == 1 && temp->c == 36)
			pivot2 = 1;
		if (pivot2 == 1)
			temp->value = _DOLLAR;
		temp = temp->next;
	}
	transform_value_for_dollar_exeption(begin);
	transform_value_for_dollar_exeption2(begin);
}

void	transform_value_for_dollar(t_first_parse **begin)
{
	t_first_parse	*temp;
	int				pivot;

	temp = NULL;
	temp = *begin;
	pivot = 0;
	while (temp != NULL)
	{
		if (temp->value == _DOLLAR)
			pivot = 1;
		if (pivot == 1 && temp->value != EXP && temp->value != _DOLLAR)
			pivot = 0;
		if (pivot == 1)
			temp->value = _DOLLAR;
		temp = temp->next;
	}
	transform_value_for_dollar_inside_double_quote(begin, 0);
}

void	transform_value_inside_quote(t_first_parse **begin)
{
	t_first_parse	*temp;
	int				doublequote;
	int				quote;

	doublequote = 0;
	quote = 0;
	temp = *begin;
	while (temp != NULL)
	{
		if ((doublequote % 2) == 1 && temp->value != _DOUBLE_QUOTE)
		{
			temp->value = EXP;
		}
		if ((quote % 2) == 1 && temp->value != _QUOTE)
			temp->value = EXP;
		if (temp->value == _QUOTE && doublequote % 2 == 0)
			quote++;
		if (temp->value == _DOUBLE_QUOTE && quote % 2 == 0)
			doublequote++;
		temp = temp->next;
	}
}

int	check_quote_number(t_first_parse **begin, t_minishell *m)
{
	t_first_parse	*temp;
	int				doublequote;
	int				quote;

	doublequote = 0;
	quote = 0;
	temp = *begin;
	while (temp != NULL)
	{
		if (temp->value == _DOUBLE_QUOTE)
			doublequote++;
		if (temp->value == _QUOTE)
			quote++;
		temp = temp->next;
	}
	if ((doublequote % 2) == 1 || (quote % 2) == 1)
	{
		m->retour = 2;
		return (error1(1) + 1);
	}
	return (0);
}

int	check_multi_special_char(t_first_parse **begin, t_first_parse *temp, int a,
		char lastchar)
{
	if (*begin != NULL)
	{
		temp = *begin;
		lastchar = temp->c;
		temp = temp->next;
	}
	while (temp != NULL)
	{
		if (lastchar == temp->c)
			a++;
		else
			a = 0;
		if (a == 1 && temp->value == _PIPE)
			return (error1(2) + 1);
		if (a == 2 && (temp->value == _R_INPUT || temp->value == _R_OUTPUT))
		{
			if (temp->value == _R_INPUT)
				return (error1(3) + 1);
			if (temp->value == _R_OUTPUT)
				return (error1(6) + 1);
		}
		lastchar = temp->c;
		temp = temp->next;
	}
	return (0);
}
