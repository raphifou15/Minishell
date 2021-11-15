/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_1_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 05:11:59 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 00:32:40 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	transform_value_to_delimiteur_2(t_first_parse *temp)
{
	while (temp != NULL && temp->value == _R_INPUT)
	{
		temp->value = _DELIMITEUR_2;
		temp = temp->next;
	}
}

static int	ft_check_if_transform_r_input(t_first_parse *temp)
{
	int	i;

	i = 0;
	while (temp != NULL && temp->value == _R_INPUT)
	{
		i++;
		temp = temp->next;
	}
	if (i != 2)
		return (0);
	while (temp != NULL && temp->value == _SPACE)
		temp = temp->next;
	while (temp != NULL && (temp->value == EXP || temp->value == _DOLLAR))
		temp = temp->next;
	if (temp != NULL && (temp->value == _QUOTE || temp->value == _DOUBLE_QUOTE))
		return (1);
	return (0);
}

void	transform_value_for_here_doc(t_first_parse **begin)
{
	t_first_parse	*temp;

	temp = *begin;
	while (temp != NULL)
	{
		if (temp->value == _R_INPUT)
		{
			if (ft_check_if_transform_r_input(temp) == 1)
				transform_value_to_delimiteur_2(temp);
			else
			{
				while (temp != NULL && temp->value == _R_INPUT)
					temp = temp->next;
			}
		}
		if (temp != NULL)
			temp = temp->next;
	}
}

void	transform_special_dollar_value(t_first_parse *temp)
{
	while (temp != NULL)
	{
		if (temp->value == _DOLLAR && (temp->c == '/' || temp->c == '!'
				|| temp->c == '?'))
		{
			temp->value = EXP;
			if (temp->next != NULL)
				temp = temp->next;
			while (temp != NULL && temp->value == _DOLLAR && temp->c != '$')
			{
				temp->value = EXP;
				temp = temp->next;
			}
		}
		if (temp != NULL && temp->next != NULL && temp->c == '$'
			&& temp->next->c == '?')
			temp = temp->next;
		if (temp != NULL)
			temp = temp->next;
	}
}
