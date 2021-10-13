/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 00:29:21 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/14 01:04:07 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_push_back_env(t_env **begin, char *str)
{
	(void)str;
	(void)begin;
	return (0);
}

int	add_env_variable_to_list(t_minishell *m, char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		ft_list_push_back_env(&m->e, env[i]);
	}
	return (0);
}
