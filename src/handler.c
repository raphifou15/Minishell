/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 04:19:22 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/05 04:29:25 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_default(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		ft_putstr(" \n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
