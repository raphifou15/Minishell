/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 04:53:15 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/13 19:56:24 by rkhelif          ###   ########.fr       */
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
	t_env	*temp;
	int		nb_lines;
	char	**env;
	int		i;

	temp = e;
	i = 0;
	nb_lines = nbr_line_inside_env(e);
	env = malloc(sizeof(char *) * (nb_lines + 1));
	if (env == NULL)
		return (NULL);
	while (temp != NULL)
	{
		env[i] = ft_join3(temp->name, "=", temp->ctn);
		if (env[i] == NULL)
			return (ft_free_double_tab(env));
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
