/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:25:13 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 19:04:15 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	built_in_unset_2(t_env *tmp_env, t_env *env, t_minishell *m, int i)
{
	if (tmp_env != NULL)
	{
		if (i == 0)
			tmp_env = tmp_env->next;
		delete_elem_env(env, i - 1);
		if (i == 0)
		{
			env = tmp_env;
			m->e = env;
		}
	}
}

static int	check_unset_name(char *s)
{
	int	i;

	i = 1;
	if (ft_is_char(s[0]) == 0)
		return (0);
	while (s[i])
	{
		if (ft_is_char(s[i]) == 0 && s[i] != '_'
			&& !(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	xcheckname(t_minishell *m, char *name)
{
	if (check_unset_name(name) == 0)
	{
		ft_putstr_err("\e[15;31mbash: unset: \'");
		ft_putstr_err(name);
		ft_putstr_err("\': not a valid identifier\e[0m\n");
		m->retour = 1;
		return (0);
	}
	return (1);
}

void	built_in_unset(t_env *env, t_minishell *m
			, t_second_parse *tmp_arg, int i)
{
	t_env			*tmp_env;

	while (tmp_arg != NULL && tmp_arg->value != _PIPE)
	{
		env = m->e;
		tmp_env = env;
		i = 0;
		if (xcheckname(m, tmp_arg->str) != 0)
		{
			if (ft_strcmp(tmp_arg->str, "_") == 0)
			{
				tmp_arg = tmp_arg->next;
				if (tmp_arg == NULL)
					return ;
			}
			while (tmp_env != NULL && ft_strcmp2(tmp_arg->str
					, tmp_env->name) != 0)
			{
				tmp_env = tmp_env->next;
				i++;
			}
			built_in_unset_2(tmp_env, env, m, i);
		}
		tmp_arg = tmp_arg->next;
	}
}
