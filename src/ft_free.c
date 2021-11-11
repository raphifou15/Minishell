/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 21:22:14 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/11 20:32:07 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free(char *str)
{
	if (str == NULL)
		return (0);
	free(str);
	str = NULL;
	return (0);
}

char	*ft_free_null(char *str)
{
	if (str == NULL)
		return (0);
	free(str);
	str = NULL;
	return (str);
}

void	ft_free2(void *data)
{
	free(data);
	data = NULL;
}

int	ft_free_all_the_list(t_first_parse *begin)
{
	t_first_parse	*temp;
	t_first_parse	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp = begin;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		ft_free2(temp2);
	}
	return (0);
}

int	ft_free_all_the_list_2(t_second_parse *begin)
{
	t_second_parse	*temp;
	t_second_parse	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp = begin;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		if (temp2->str != NULL)
			ft_free(temp2->str);
		ft_free2(temp2);
	}
	return (0);
}
