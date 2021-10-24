/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 04:53:15 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/24 06:08:52 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_line_inside_env(t_env *e)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = e;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**env_list_to_tab(t_env *e)
{
	int		nb_lines;
	char	**tab;

	nb_lines = nbr_line_inside_env(e);
	tab = malloc(sizeof(char *) * (nb_lines + 1));
	if (tab == NULL)
		return (NULL);
	free(tab);
	return (NULL);
}
