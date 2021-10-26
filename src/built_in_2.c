/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 04:55:58 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/26 20:11:10 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_pwd(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL && ft_strcmp(temp->name, "_") != 0)
		temp = temp->next;
	ft_putstr(temp->ctn);
	ft_putstr("\n");
}
