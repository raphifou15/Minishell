/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:18:44 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 18:34:07 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *begin)
{
	int		i;
	t_env	*temp;

	temp = begin;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

char	**tab_init(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}

void	free_inside_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
}
