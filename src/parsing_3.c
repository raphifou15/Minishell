/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <alebross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 23:42:09 by alebross          #+#    #+#             */
/*   Updated: 2021/10/16 23:13:17 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_push_back_3(t_second_parse **begin, t_second_parse *p2)
{
	t_second_parse	*new;
	t_second_parse	*temp;

	new = NULL;
	new = ft_create_elem_3(p2);
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

t_second_parse	*ft_create_elem_3(t_second_parse *p2)
{
	t_second_parse	*elem;

	elem = NULL;
	elem = malloc(sizeof(*elem));
	if (elem == NULL)
		return (NULL);
	elem->value = p2->value;
	elem->str = ft_strdup(p2->str);
	if (elem->str == NULL)
		return (NULL);
	if (p2->value == 0)
	{
		while (p2->next != NULL && p2->next->value == EXP)
		{
			p2 = p2->next;
			elem->str = ft_strjoin(elem->str, p2->str);
			if (elem->str == NULL)
				return (NULL);
		}
	}
	elem->next = NULL;
	return (elem);
}

int	parsing_3_part_0(t_minishell *m)
{
	t_second_parse	*temp;

	temp = NULL;
	temp = m->p2;
	while (temp != NULL)
	{
		if (ft_list_push_back_3(&m->p3, temp) != 0)
			return (ft_free_all_the_list_2(m->p3) + 1);
		if (temp->value != EXP)
			temp = temp->next;
		else
		{
			while (temp != NULL && temp->value == EXP)
				temp = temp->next;
		}
	}
	return (0);
}

int	parsing_3(t_minishell *m)
{
	if (parsing_3_part_0(m) != 0)
		return (1);
	display_elem_2(m->p3);
	return (0);
}
