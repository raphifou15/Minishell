/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 02:58:39 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/11 20:00:22 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error1(int err)
{
	if (err == 0)
		ft_putstr_err("\e[15;31mError malloc failed\e[0m\n");
	if (err == 1)
	{
	ft_putstr_err("\e[15;31mError syntax error (double ");
	ft_putstr_err("quote or simple quote are not close)\e[0m\n");
	}
return (0);
}