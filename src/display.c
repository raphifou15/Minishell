/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 05:36:19 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/13 20:15:27 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_elem(t_first_parse *begin)
{
	t_first_parse	*temp;

	temp = begin;
	printf("DISPLAY PARSING1:\n");
	while (temp != NULL)
	{
		printf("%d = value    %c = c\n", temp->value, temp->c);
		temp = temp->next;
	}
}

void	display_elem_2(t_second_parse *begin)
{
	t_second_parse	*temp;

	temp = begin;
	printf("DISPLAY PARSING2:\n");
	while (temp != NULL)
	{
		printf("%d = value    %s = string\n", temp->value, temp->str);
		temp = temp->next;
	}
}
