/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <alebross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:56:01 by alebross          #+#    #+#             */
/*   Updated: 2021/10/11 19:58:51 by alebross         ###   ########.fr       */
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

int		check_quote_number(t_first_parse **begin)
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
		return (error1(1) + 1);
	return (0);
}
