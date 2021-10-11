/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <alebross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 23:42:09 by alebross          #+#    #+#             */
/*   Updated: 2021/10/12 01:51:42 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_push_back_2(t_second_parse **begin, t_first_parse *p1, int len)
{
	t_second_parse	*new;
	t_second_parse	*temp;

	new = NULL;
	new = ft_create_elem_2(p1, len);
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

t_second_parse	*ft_create_elem_2(t_first_parse *p1, int len)
{
	t_second_parse	*elem;
	t_first_parse	*temp;
	int				i;

	i = 0;
	temp = p1;
	elem = NULL;
	elem = malloc(sizeof(*elem));
	if (elem == NULL)
		return (NULL);
	elem->str = malloc(sizeof(char) * (len + 1));
	if (elem->str == NULL)
		return (NULL);
	elem->value = temp->value;
	while (len > 0)
	{
		elem->str[i] = temp->c;
		temp = temp->next;
		i++;
		len--;
	}
	elem->str[i] = '\0';
	elem->next = NULL;
	return (elem);
}

int		next_parse_len(t_first_parse *begin)
{
	int				i;
	int				valueb;
	t_first_parse	*temp;

	temp = begin;
	valueb = temp->value;
	i = 0;
	while (temp != NULL && temp->value == valueb)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int		parsing_2_part_0(t_minishell *m)
{
	t_first_parse	*temp;
	int				len;

	temp = NULL;
	temp = m->p1;
	while (temp != NULL)
	{
		if (temp->value != _QUOTE && temp->value != _DOUBLE_QUOTE
			&& temp->value != _SPACE)
		{
			len = next_parse_len(temp);
			if (ft_list_push_back_2(&m->p2, temp, len) != 0)
				return (ft_free_all_the_list_2(m->p2) + 1);
			while (len > 0)
			{
				temp = temp->next;
				len--;
			}
		}
		else
			temp = temp->next;
	}
	return (0);
}

int		parsing_2(t_minishell *m)
{
	if (parsing_2_part_0(m) != 0)
		return (1);
	display_elem_2(m->p2);
	return (0);
}
