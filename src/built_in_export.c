/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 22:40:30 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 19:51:55 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	built_in_export_2(t_env *env, char *str, char *name, char *ctn)
{
	t_env	*temp;

	temp = env;
	name = put_inside_name(str);
	if (name == NULL)
		return ;
	ctn = put_inside_ctn(str);
	if (ctn == NULL)
	{
		free(name);
		return ;
	}
	while (temp != NULL && ft_strcmp(temp->name, name) != 0)
		temp = temp->next;
	if (temp != NULL)
	{
		free(temp->ctn);
		temp->ctn = NULL;
		temp->ctn = ft_strdup(ctn);
	}
	else
		ft_list_push_back_env_2(&env, name, ctn);
	free(name);
	free(ctn);
	return ;
}

static void	built_in_export_3(t_env *env, char *str)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL && ft_strcmp(temp->name, str) != 0)
		temp = temp->next;
	if (temp != NULL)
		return ;
	ft_list_push_back_env_2(&env, str, NULL);
}

void	built_in_export(t_minishell *m, t_second_parse *begin, int n)
{
	t_second_parse	*temp;

	temp = begin->next;
	if (temp == NULL)
		return (ft_display_export_list(m->e, env_size(m->e), m, 0));
	while (temp != NULL && temp->value != _PIPE)
	{
		n = check_env_name(temp->str);
		if (n == 0)
		{
			ft_putstr_err("\e[15;31mbash: export: \'");
			ft_putstr_err(temp->str);
			ft_putstr_err("\': not a valid identifier\e[0m\n");
			m->retour = 1;
		}
		else if (n == 3)
			built_in_export_4(m->e, temp->str, NULL, NULL);
		else if (n == 2)
			built_in_export_2(m->e, temp->str, NULL, NULL);
		else if (n == 1)
			built_in_export_3(m->e, temp->str);
		temp = temp->next;
	}
}
