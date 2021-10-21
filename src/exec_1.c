/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 05:55:52 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/21 21:15:51 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executing(t_minishell *m)
{
	(void)m;
	printf("Nous ferons l'execution plus tard\n");
}

//int	ft_find_number_elem_p3(t_second_parse *begin)
//{
//	int				i;
//	t_second_parse	*temp;
//
//	i = 0;
//	temp = begin;
//	while (temp != NULL)
//	{
//		i++;
//		temp = temp->next;
//	}
//	return (i);
//}
//
//int	ft_check_if_redirection(t_second_parse *begin)
//{
//	int				i;
//	t_second_parse	*temp;
//
//	i = 0;
//	temp = begin;
//	while (temp != NULL)
//	{
//		if (temp->value != EXP && temp->value != _SPACE)
//			i++;
//		temp = temp->next;
//	}
//	return (i);
//}
//
//void	execution_without_pipe(t_minishell *m)
//{
//	int	nb_elem;
//	int	redirection;
//
//	nb_elem = ft_find_number_elem_p3(m->p3);
//	redirection = ft_check_if_redirection(m->p3);
//	(void)nb_elem;
//	printf("%d = redirection\n", redirection);
//}
//
//int	check_numb_of_pipe(t_second_parse	*begin)
//{
//	t_second_parse	*temp;
//	int				i;
//
//	i = 0;
//	temp = begin;
//	while (temp != NULL)
//	{
//		if (temp->value == _PIPE)
//			i++;
//		temp = temp->next;
//	}
//	return (i);
//}
//
//void	executing(t_minishell *m)
//{
//	int				nb_pipe;
//	t_second_parse	*temp;
//
//	temp = m->p3;
//	nb_pipe = check_numb_of_pipe(m->p3);
//	if (nb_pipe == 0)
//		return (execution_without_pipe(m));
//	while (nb_pipe != 0)
//	{
//		printf("lala\n");
//		while (temp->value != _PIPE)
//			temp = temp->next;
//		temp = temp->next;
//		nb_pipe = check_numb_of_pipe(temp);
//	}
//}
