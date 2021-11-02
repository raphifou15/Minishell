/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_1_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 05:11:59 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/31 18:33:58 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transform_value_to_delimiteur_2(t_first_parse *temp)
{
	while (temp != NULL && temp->value == _R_INPUT)
	{
		temp->value = _DELIMITEUR_2;
		temp = temp->next;
	}
}

int	ft_check_if_transform_r_input(t_first_parse *temp)
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
	while (temp != NULL && temp->value == EXP)
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
				while (temp->value == _R_INPUT)
					temp = temp->next;
			}
		}
		if (temp != NULL)
			temp = temp->next;
	}
}