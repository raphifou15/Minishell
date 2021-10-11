/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_value_inside_quote.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <alebross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:07:53 by alebross          #+#    #+#             */
/*   Updated: 2021/10/11 18:12:46 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			temp->value = EXP;
		if ((quote % 2) == 1 && temp->value != _QUOTE)
			temp->value = EXP;
		if (temp->value == _QUOTE && doublequote % 2 == 0)
			quote++;
		if (temp->value == _DOUBLE_QUOTE && quote % 2 == 0)
			doublequote++;
		temp = temp->next;
	}
}
