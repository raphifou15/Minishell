/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:22:08 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 18:22:20 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (temp->ctn != NULL)
		{
			ft_putstr(temp->name);
			ft_putstr("=");
			ft_putstr(temp->ctn);
			ft_putstr("\n");
		}
		temp = temp->next;
	}
}
