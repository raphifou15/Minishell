/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 04:55:58 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/29 22:46:12 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) != 0)
		ft_putstr(pwd);
	else
		ft_putstr("Error");
	ft_putstr("\n");
}

void	delete_elem_env(t_env *begin, int be)
{
	int		i;
	t_env	*temp;
	t_env	*temp2;

	temp = begin;
	i = 0;
	if (i > be)
	{
		ft_free(temp->name);
		ft_free(temp->ctn);
		ft_free2(temp);
		return ;
	}
	while (temp != NULL && i < be)
	{
		temp = temp->next;
		i++;
	}
	temp2 = temp;
	temp = temp->next;
	temp2->next = temp->next;
	ft_free(temp->name);
	ft_free(temp->ctn);
	ft_free2(temp);
}

void	built_in_unset(t_env *env, t_minishell *m, t_second_parse *begin, int i)
{
	t_env			*tmp_env;
	t_second_parse	*tmp_arg;

	tmp_arg = begin->next;
	while (tmp_arg != NULL && tmp_arg->value != _PIPE)
	{
		tmp_env = env;
		i = 0;
		while (tmp_env != NULL && strcmp(tmp_arg->str, tmp_env->name) != 0)
		{
			tmp_env = tmp_env->next;
			i++;
		}
		if (tmp_env != NULL)
		{
			if (i == 0)
				tmp_env = tmp_env->next;
			delete_elem_env(env, i - 1);
			if (i == 0)
				env = tmp_env;
			if (i == 0)
				m->e = env;
		}
		tmp_arg = tmp_arg->next;
	}
}
