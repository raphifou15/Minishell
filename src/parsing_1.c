/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 21:30:18 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/11 05:31:38 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_push_back(t_first_parse **begin, char c, int b)
{
	t_first_parse	*new;
	t_first_parse	*temp;

	new = NULL;
	new = ft_create_elem(c, b);
	if (new == NULL)
		return (error1(0) + 1);
	if (*begin == NULL)
	{
		*begin = new;
		return (0);
	}
	temp = *begin;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	return (0);
}

int	find_the_good_value(char c)
{
	(void)c;
	return (EXP);
}

t_first_parse	*ft_create_elem(char c, int b)
{
	t_first_parse	*elem;

	elem = NULL;
	elem = malloc(sizeof(*elem));
	if (elem == NULL)
		return (NULL);
	elem->c = c;
	elem->value = b;
	elem->next = NULL;
	return (elem);
}

int	parsing_1_part_0(t_minishell *m, int i)
{
	int	value;

	while (rl_line_buffer[++i] != '\0')
	{
		value = find_the_good_value(rl_line_buffer[i]);
		if (ft_list_push_back(&m->p1, rl_line_buffer[i], value) == 1)
			return (ft_free_all_the_list(m->p1) + 1);
	}
	return (0);
}
