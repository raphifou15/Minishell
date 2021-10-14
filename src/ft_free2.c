/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 03:20:40 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/14 03:39:08 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_all_elem_env(t_env *begin)
{
	t_env	*temp;
	t_env	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp = begin;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		if (temp2->name != NULL)
			ft_free(temp2->name);
		if (temp2->ctn != NULL)
			ft_free(temp2->ctn);
		ft_free2(temp2);
	}
	return (0);
}
