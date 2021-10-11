/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 05:36:19 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/11 05:45:55 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_elem(t_first_parse *begin)
{
	t_first_parse	*temp;

	temp = begin;
	while (temp != NULL)
	{
		printf("%d = value    %c = c\n", temp->value, temp->c);
		temp = temp->next;
	}
}
