/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 00:29:21 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/08 01:47:32 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_inside_name(char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i] != '\0' && src[i] != '=')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != '=')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*put_inside_ctn(char *src)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (src[i] != '\0' && src[i] != '=')
		i++;
	if (src[i] == '=')
		i++;
	while (src[i] != '\0' && ++len != 0)
		i++;
	str = malloc(sizeof(char *) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (src[i] != '\0' && src[i] != '=')
		i++;
	if (src[i] == '=')
		i++;
	while (src[i] != '\0')
		str[len++] = src[i++];
	str[len] = '\0';
	return (str);
}

static t_env	*ft_create_elem_env(char *str)
{
	t_env	*elem;

	elem = NULL;
	elem = malloc(sizeof(*elem));
	if (elem == NULL)
		return (NULL);
	elem->name = put_inside_name(str);
	if (elem->name == NULL)
		return (ft_free3(elem));
	elem->ctn = put_inside_ctn(str);
	if (elem->ctn == NULL)
	{
		elem->name = ft_free_null(elem->name);
		return (ft_free3(elem));
	}
	elem->next = NULL;
	return (elem);
}

static int	ft_list_push_back_env(t_env **begin, char *str)
{
	t_env	*new;
	t_env	*temp;

	new = NULL;
	new = ft_create_elem_env(str);
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

int	add_env_variable_to_list(t_minishell *m, char **env)
{
	int	i;

	i = -1;
	while (env != NULL && env[++i] != NULL)
	{
		if (ft_list_push_back_env(&m->e, env[i]) != 0)
			return (ft_free_all_elem_env(m->e) + 1);
	}
	return (0);
}
