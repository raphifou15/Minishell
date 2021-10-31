/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 00:26:05 by alebross          #+#    #+#             */
/*   Updated: 2021/10/31 19:14:02 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	actualise_pwd(t_env *env, char *name)
{
	t_env	*temp;
	char	*pwd;

	temp = env;
	while (temp != NULL && ft_strcmp(temp->name, name) != 0)
		temp = temp->next;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (error2(errno));
	if (temp != NULL)
	{
		free(temp->ctn);
		temp->ctn = NULL;
		temp->ctn = ft_strdup(pwd);
	}
	else
	{
		if (ft_list_push_back_env_2(&env, name, pwd) == 1)
		{
			free(pwd);
			return ;
		}
	}
	free(pwd);
}

void	built_in_cd(t_minishell *m, t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;

	temp = begin;
	i = 0;
	while (temp != NULL && temp->value != _PIPE)
	{
		temp = temp->next;
		i++;
	}
	if (i > 2)
		return (ft_putstr_err("minishell: cd: too many arguments\n"));
	if (i < 2)
		return ;
	actualise_pwd(m->e, "OLDPWD");
	temp = begin->next;
	if (strcmp(".", temp->str) == 0)
		return ;
	if (chdir(temp->str) == -1)
		error2(errno);
	actualise_pwd(m->e, "PWD");
}

//strdup line 29
