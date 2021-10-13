/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:57:03 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/13 06:41:26 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_elem_dollar_part2(t_second_parse *temp)
{
	(void)temp;
	return (0);
}

int	change_elem_dollar(t_second_parse *begin)
{
	t_second_parse	*temp;

	temp = NULL;
	temp = begin;
	while (temp != NULL)
	{
		if (temp->value == _DOLLAR)
		{
			if (change_elem_dollar_part2(temp) != 0)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

//faire une boucle a l'interieure de la fonction change_elem_dollar_part2
//le but est de prendre les bonnes valeurs stocker dans les dollars
//et de les stocker a l'interrieur temp->str
//utiliser la fonction getenv(char *str) pour recup les donnees 
