/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:55:52 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/24 02:35:12 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_nbr_pipe(t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;

	i = 0;
	temp = begin;
	while (temp != NULL)
	{
		if (temp->value == _PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	executing_without_pipe(t_second_parse *begin)
{
	(void)begin;
	printf("start executing here\n");
}

void	executing(t_second_parse *begin, t_minishell *m)
{
	t_second_parse	*temp;
	int				nbr_pipe;

	temp = begin;
	nbr_pipe = find_nbr_pipe(begin);
	if (nbr_pipe == 0)
		return (executing_without_pipe(begin));
	(void)temp;
	(void)m;
}

//Tram de l'histoire 
//chercher le nombre de pipe;
//
