/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:57:41 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 18:02:12 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_for_env_name(char c)
{
	if (ft_is_char(c) == 1 || (c >= '0' && c <= '9'))
		return (1);
	if (c == '_' || c == '/')
		return (1);
	return (0);
}

int	check_env_name(char *s)
{
	int	i;

	i = 1;
	if (ft_is_char(s[0]) == 0 && s[0] != '_')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (3);
		if (s[i] == '=')
			return (2);
		if (char_for_env_name(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*put_inside_name_2(char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i] != '\0' && src[i] != '+')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != '+')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	built_in_export_4(t_env *env, char *str, char *name, char *ctn)
{
	t_env	*temp;

	temp = env;
	name = put_inside_name_2(str);
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
		temp->ctn = ft_strjoin(temp->ctn, ctn);
	}
	else
		ft_list_push_back_env_2(&env, name, ctn);
	free(name);
	free(ctn);
	return ;
}
