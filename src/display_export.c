/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:18:44 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 19:02:31 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_line_to_str(t_env *temp)
{
	char	*str;

	str = ft_strdup(temp->name);
	if (str == NULL)
		return (NULL);
	if (temp->ctn != NULL)
	{
		str = ft_strjoin(str, "=\"");
		if (str == NULL)
			return (NULL);
		str = ft_strjoin(str, temp->ctn);
		if (str == NULL)
			return (NULL);
		str = ft_strjoin(str, "\"");
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	**sort_str_tab(char **tab, int s)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = 0;
	i = 0;
	j = 0;
	while (i < s)
	{
		j = i;
		while (j < s)
		{
			if (ft_strcmp2(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void	display_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '_' && tab[i][1] == '=')
			i++;
		else
		{
			ft_putstr(tab[i]);
			ft_putstr("\n");
			i++;
		}
	}
}

void	ft_display_export_list_2(char **tab, int i, int s)
{
	tab[i] = NULL;
	tab = sort_str_tab(tab, s);
	display_tab(tab);
	free_inside_tab(tab);
	free(tab);
}

void	ft_display_export_list(t_env *begin, int s, t_minishell *m, int i)
{
	t_env	*temp;
	char	**tab;

	tab = malloc(sizeof(char *) * (s + 1));
	if (tab == NULL)
	{
		m->retour = 1;
		return (error4("Error malloc failed"));
	}
	tab = tab_init(tab, s + 1);
	temp = begin;
	while (temp != NULL)
	{
		tab[i] = export_line_to_str(temp);
		if (tab[i] == NULL)
		{
			m->retour = 1;
			free_inside_tab(tab);
			free(tab);
			return (error4("Error malloc failed"));
		}
		i++;
		temp = temp->next;
	}
	ft_display_export_list_2(tab, i, s);
}
