/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 22:40:06 by alebross          #+#    #+#             */
/*   Updated: 2021/11/07 23:14:33 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	actualise_oldpwd(t_env *env)
{
	t_env	*temp;
	char	*oldpwd;

	temp = env;
	while (temp != NULL && ft_strcmp(temp->name, "PWD") != 0)
		temp = temp->next;
	if (temp == NULL)
		oldpwd = NULL;
	else
		oldpwd = ft_strdup(temp->ctn);
	temp = env;
	while (temp != NULL && ft_strcmp(temp->name, "OLDPWD") != 0)
		temp = temp->next;
	if (temp != NULL)
	{
		free(temp->ctn);
		temp->ctn = ft_strdup(oldpwd);
	}
	if (oldpwd != NULL)
		free(oldpwd);
}

static void	actualise_pwd(t_env *env)
{
	t_env	*temp;
	char	*pwd;

	temp = env;
	while (temp != NULL && ft_strcmp(temp->name, "PWD") != 0)
		temp = temp->next;
	if (temp == NULL)
		return ;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (error2(errno));
	free(temp->ctn);
	temp->ctn = NULL;
	temp->ctn = ft_strdup(pwd);
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
	temp = begin->next;
	if (strcmp(".", temp->str) == 0)
		return ;
	if (chdir(temp->str) == -1)
		error2(errno);
	actualise_oldpwd(m->e);
	actualise_pwd(m->e);
}
