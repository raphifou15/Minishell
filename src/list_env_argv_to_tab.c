/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_argv_to_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:27:39 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/29 04:12:46 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_elem_access(t_second_parse *begin, char **tab)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	while (tab != NULL && tab[++i] != NULL)
	{
		str = ft_join3(tab[i], "/", begin->str);
		if (str == NULL)
		{
			ft_free_double_tab(tab);
			return (NULL);
		}
		if (access(str, X_OK) == 0)
			return (str);
		free(str);
		str = NULL;
	}
	str = ft_calloc(sizeof(char), 1);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*way_of_path(t_env *env)
{
	t_env	*temp;
	char	*str;

	temp = env;
	while ((temp != NULL) && (ft_strcmp(temp->name, "PATH") == 1))
		temp = temp->next;
	if (temp == NULL)
		str = ft_calloc(sizeof(char), 1);
	else
		str = ft_strdup(temp->ctn);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	**list_env_argv_to_tab(t_second_parse *begin, t_env *env)
{
	char	*str;
	char	**tab;

	str = way_of_path(env);
	if (str == NULL)
		return (NULL);
	if (str[0] == '\0' && ft_free(str) == 0)
		return (argv_list_to_tab(begin));
	tab = ft_split(str, ':');
	str = ft_free_null(str);
	if (tab == NULL)
		return (NULL);
	str = find_elem_access(begin, tab);
	if (str == NULL)
		return (NULL);
	ft_free_double_tab(tab);
	if (str[0] == '\0' && ft_free(str) == 0)
		return (argv_list_to_tab(begin));
	free(begin->str);
	begin->str = NULL;
	begin->str = ft_strdup(str);
	if (begin->str == NULL && ft_free(str) == 0)
		return (NULL);
	str = ft_free_null(str);
	return (argv_list_to_tab(begin));
}