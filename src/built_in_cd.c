/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 22:40:06 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 17:51:52 by alebross         ###   ########.fr       */
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

static void	actualise_pwd(t_env *env, int o)
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
	if (o == 1)
	{
		ft_putstr(pwd);
		ft_putstr("\n");
	}
	free(temp->ctn);
	temp->ctn = NULL;
	temp->ctn = ft_strdup(pwd);
	free(pwd);
}

static void	built_in_cd_3(t_minishell *m, char *name)
{
	t_env	*temp;

	temp = m->e;
	while (temp != NULL && ft_strcmp(temp->name, name) != 0)
		temp = temp->next;
	if (temp == NULL || temp->ctn == NULL || temp->ctn[0] == '\0')
	{
		m->retour = 1;
		ft_putstr_err("\e[15;31mminishell: cd: ");
		ft_putstr_err(name);
		ft_putstr_err(" not set\n\e[0m");
		return ;
	}
	if (chdir(temp->ctn) == -1)
	{
		error2(errno);
		m->retour = 1;
	}
	actualise_oldpwd(m->e);
	if (ft_strcmp(name, "OLDPWD") == 0)
		actualise_pwd(m->e, 1);
	else
		actualise_pwd(m->e, 0);
}

static void	built_in_cd_2(t_minishell *m, char *str)
{
	if (chdir(str) == -1)
	{
		error2(errno);
		m->retour = 1;
	}
	actualise_oldpwd(m->e);
	actualise_pwd(m->e, 0);
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
	{
		m->retour = 1;
		return (error4("minishell: cd: too many arguments"));
	}
	if (i == 1)
		return (built_in_cd_3(m, "HOME"));
	temp = begin->next;
	if (strcmp(".", temp->str) == 0)
		return ;
	if (strcmp("-", temp->str) == 0)
		return (built_in_cd_3(m, "OLDPWD"));
	built_in_cd_2(m, temp->str);
}
