/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_1_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 03:34:59 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/08 21:07:03 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transform_value_for_dollar_exeption(t_first_parse **begin)
{
	t_first_parse	*temp;
	t_first_parse	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp = *begin;
	while (temp != NULL)
	{
		if (temp->value == _DOLLAR && temp->c == '$')
		{
			if ((temp->next != NULL) && (temp->next->c == '?'))
			{
				temp2 = temp->next->next;
				while (temp2 != NULL && temp2->value == _DOLLAR
					&& temp2->c != '$')
				{
					temp2->value = EXP;
					temp2 = temp2->next;
				}
			}
		}
		temp = temp->next;
	}
}

void	transform_value_for_dollar_exeption2(t_first_parse **begin)
{
	t_first_parse	*temp;
	int				i;

	temp = *begin;
	i = 0;
	while (temp != NULL)
	{
		if (temp->value == _DOUBLE_QUOTE)
			i = 0;
		if (temp->value == _DOLLAR && (temp->c == '$' || temp->c == 39))
			i = 0;
		if (i == 0 && temp->value == _DOLLAR)
			i = 1;
		if (i == 1 && temp->c == 39)
			i = 2;
		if (i == 2 && temp->value != _DOUBLE_QUOTE)
			temp->value = EXP;
		temp = temp->next;
	}
}

static int	ft_check_if_null(t_first_parse *temp, int q, int qq)
{
	while (temp != NULL && (temp->value == q || temp->value == qq))
		temp = temp->next;
	if (temp == NULL)
		return (0);
	if (temp->value == _SPACE)
		return (0);
	return (1);
}

static void	transform_to_empty_quote_value(t_first_parse *temp, int q, int qq)
{
	while (temp != NULL && (temp->value == q || temp->value == qq))
	{
		temp->value = _QUOTE_EMPTY;
		temp = temp->next;
	}
}

void	transform_value_quote(t_first_parse **begin)
{
	t_first_parse	*temp;
	int				i;

	i = 0;
	temp = *begin;
	while (temp != NULL)
	{
		if (i == 0 && (temp->value == _QUOTE || temp->value == _DOUBLE_QUOTE))
		{
			if (ft_check_if_null(temp, _QUOTE, _DOUBLE_QUOTE) == 0)
				transform_to_empty_quote_value(temp, _QUOTE, _DOUBLE_QUOTE);
		}
		if (i != 0 && (temp->value == _SPACE && temp->next != NULL
				&& (temp->next->value == _QUOTE
					|| temp->next->value == _DOUBLE_QUOTE)))
		{
			if (ft_check_if_null(temp->next, _QUOTE, _DOUBLE_QUOTE) == 0)
				transform_to_empty_quote_value(temp->next, _QUOTE,
					_DOUBLE_QUOTE);
		}
		temp = temp->next;
		i++;
	}
}
