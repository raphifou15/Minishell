/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 22:40:30 by alebross          #+#    #+#             */
/*   Updated: 2021/11/07 23:26:36 by rkhelif          ###   ########.fr       */
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

void	built_in_export(t_minishell *m, t_second_parse *begin)
{
	begin = begin->next;
	if (begin == NULL)
	{
		ft_display_export_list(m->e);
		return ;
	}
	if (ft_is_char(begin->str[0]) != 1)
	{
		ft_putstr_err("bash: export: \'");
		ft_putstr_err(begin->str);
		ft_putstr_err("\': not a valid identifier\n");
		return ;
	}
	while (begin != NULL)
	{
		if (ft_strchr2(begin->str, '=') == 1)
			built_in_export_2(m->e, begin->str, NULL, NULL);
		else
			built_in_export_3(m->e, begin->str);
		begin = begin->next;
	}
}

//strdup line 29
