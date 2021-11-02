/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:31:31 by alebross          #+#    #+#             */
/*   Updated: 2021/11/02 18:52:32 by alebross         ###   ########.fr       */
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
	if (elem->ctn == NULL && ctn != NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}

t_env	*init_env3(t_env *env, char *name, char *ctn)
{
	if (ctn == NULL)
	{
		ft_free_all_elem_env(env);
		free(name);
		free(ctn);
		return (NULL);
	}
	if (ft_list_push_back_env_2(&env, name, ctn) == 1)
	{
		ft_free_all_elem_env(env);
		free(name);
		free(ctn);
		return (NULL);
	}
	free(name);
	free(ctn);
	if (ft_list_push_back_env_2(&env, "OLDPWD", NULL) == 1)
	{
		ft_free_all_elem_env(env);
		return (NULL);
	}
	return (env);
}

t_env	*init_env2(t_env *env, char *name, char *ctn)
{
	free(ctn);
	ctn = NULL;
	name = malloc(sizeof(char) * 2);
	if (name == NULL)
	{
		ft_free_all_elem_env(env);
		return (NULL);
	}
	name[0] = '_';
	name[1] = '\0';
	ctn = getcwd(NULL, 0);
	if (ctn == NULL)
	{
		ft_free_all_elem_env(env);
		free(name);
		return (NULL);
	}
	ctn = ft_strjoin(ctn, "./minishell");
	return (init_env3(env, name, ctn));
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
	if (ft_list_push_back_env_2(&env, name, ctn) == 1)
	{
		free(name);
		free(ctn);
		return (NULL);
	}
	free(name);
	name = NULL;
	return (init_env2(env, name, ctn));
}
