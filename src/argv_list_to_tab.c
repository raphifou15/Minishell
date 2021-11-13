/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_list_to_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 02:03:28 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/13 20:05:40 by rkhelif          ###   ########.fr       */
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

char	**argv_list_to_tab(t_second_parse *begin, int i)
{
	t_second_parse	*temp;
	int				nbr_argv;
	char			**argv;

	temp = begin;
	nbr_argv = find_nbr_argv(begin);
	argv = malloc(sizeof(char *) * (nbr_argv + 1));
	if (argv == NULL)
		return (NULL);
	while (temp != NULL && temp->value != _PIPE)
	{
		argv[i] = ft_strdup(temp->str);
		if (argv[i] == NULL)
		{
			while (--i > -1)
				free(argv[i]);
			free(argv);
			return (NULL);
		}
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

char	**argv_inside_multi_pipe_norme(t_second_parse *temp, t_minishell *m,
		char **argv)
{
	if (absolute_way(temp) == 1)
		argv = argv_list_to_tab(temp, 0);
	else
		argv = list_env_argv_to_tab(temp, m->e);
	return (argv);
}
