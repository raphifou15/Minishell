/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_1_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 03:34:59 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/24 02:35:08 by rkhelif          ###   ########.fr       */
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
