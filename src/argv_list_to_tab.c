/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_list_to_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 02:03:28 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/26 18:59:11 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_nbr_argv(t_second_parse *begin)
{
	t_second_parse	*temp;
	int				i;

	i = 0;
	temp = begin;
	while (temp != NULL && temp->value != _PIPE)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**argv_list_to_tab(t_second_parse *begin)
{
	t_second_parse	*temp;
	int				nbr_argv;
	char			**argv;
	int				i;

	i = 0;
	temp = begin;
	nbr_argv = find_nbr_argv(begin);
	argv = malloc(sizeof(char *) * (nbr_argv + 1));
	if (argv == NULL)
		return (NULL);
	while (temp != NULL && temp->value != _PIPE)
	{
		argv[i] = ft_strdup(temp->str);
		if (argv[i] == NULL)
			return (NULL);
		i++;
		temp = temp->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	absolute_way(t_second_parse *begin)
{
	if (begin->str[0] == '/')
		return (1);
	if (begin->str[0] == '.')
		return (1);
	return (0);
}
