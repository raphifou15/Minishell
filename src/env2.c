/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:31:31 by alebross          #+#    #+#             */
/*   Updated: 2021/10/30 20:39:38 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_push_back_env_2(t_env **begin, char *name, char *ctn)
{
	t_env	*new;
	t_env	*temp;

	new = NULL;
	new = create_elem_env(name, ctn);
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

t_env	*create_elem_env(char *name, char *ctn)
{
	t_env	*elem;

	elem = NULL;
	elem = malloc(sizeof(*elem));
	elem->name = NULL;
	elem->ctn = NULL;
	if (elem == NULL)
		return (NULL);
	elem->name = ft_strdup(name);
	if (elem->name == NULL)
		return (NULL);
	elem->ctn = ft_strdup(ctn);
	if (elem->ctn == NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}

t_env	*init_env(char *name, char *ctn)
{
	t_env	*env;

	env = NULL;
	name = ft_strdup("PWD");
	if (name == NULL)
	{
		ft_putstr_err("Error malloc failed\n");
		return (NULL);
	}
	ctn = getcwd(NULL, 0);
	if (ctn == NULL)
	{
		error2(errno);
		free(name);
		return (NULL);
	}
	if (ft_list_push_back_env_2(&env, name, ctn))
		return (NULL);
	return (env);
}
