/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 04:55:58 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/07 23:11:04 by rkhelif          ###   ########.fr       */
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

void	built_in_unset(t_env *env, t_minishell *m, t_second_parse *begin, int i)
{
	t_env			*tmp_env;
	t_second_parse	*tmp_arg;

	tmp_arg = begin->next;
	while (tmp_arg != NULL && tmp_arg->value != _PIPE)
	{
		tmp_env = env;
		i = 0;
		if (ft_strcmp(tmp_arg->str, "_") == 0)
		{
			tmp_arg = tmp_arg->next;
			if (tmp_arg == NULL)
				return ;
		}
		while (tmp_env != NULL && strcmp(tmp_arg->str, tmp_env->name) != 0)
		{
			tmp_env = tmp_env->next;
			i++;
		}
		built_in_unset_2(tmp_env, env, m, i);
		tmp_arg = tmp_arg->next;
	}
}

void	built_in_exit(t_minishell *m, t_second_parse *begin, char *line)
{
	(void)begin;
	reboot(m, line);
	ft_free_all_elem_env(m->e);
	close(0);
	close(1);
	close(2);
	exit(0);
}
