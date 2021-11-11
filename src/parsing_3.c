/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <alebross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 23:42:09 by alebross          #+#    #+#             */
/*   Updated: 2021/11/10 19:57:31 by rkhelif          ###   ########.fr       */
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
		return (ft_free3(elem));
	if (p2->value == 0)
	{
		while (p2->next != NULL && p2->next->value == EXP)
		{
			p2 = p2->next;
			elem->str = ft_strjoin(elem->str, p2->str);
			if (elem->str == NULL)
				return (ft_free3(elem));
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
		if (temp->value == _SPACE)
			temp = temp->next;
		else
		{
			if (ft_list_push_back_3(&m->p3, temp) != 0)
			{
				m->retour = 1;
				return (ft_free_all_the_list_2(m->p3) + 1);
			}
			if (temp->value != EXP)
				temp = temp->next;
			else
			{
				while (temp != NULL && temp->value == EXP)
					temp = temp->next;
			}
		}
	}
	return (0);
}

int	parsing_3(t_minishell *m)
{
	if (parsing_3_part_0(m) != 0)
		return (1);
	if (check_error_syntax(m->p3) != 0)
	{
		m->retour = 2;
		return (ft_free_all_the_list_2(m->p3) + 1);
	}
	corrige_redirection(m->p3, m);
	corrige_empty_quote(m->p3);
	order_list(m->p3, m);
	if (check_syntax_error_pipe(m->p3) != 0)
	{
		m->retour = 2;
		return (ft_free_all_the_list_2(m->p3) + 1);
	}
	return (0);
}

// parsing_3_part_0 verifier avec bonne valeur de sortie;

//ft_create_elem_3  elem->str ligne ligne 55 est free dans la fonction strjoin
// si echoue.
