/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 02:58:39 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/11 19:17:04 by rkhelif          ###   ########.fr       */
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
	if (err == 2)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `||'\e[0m\n");
	if (err == 3)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `<<<'\e[0m\n");
	if (err == 4)
		ft_putstr_err("\e[15;31mError syntax error (invalid redirection)\e[0m\n");
	if (err == 5)
		ft_putstr_err("\e[15;31mCommand not found\e[0m\n");
	if (err == 6)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `>>>'\e[0m\n");
	if (err == 7)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `|'\e[0m\n");
	return (0);
}

void	error2(int err)
{
	ft_putstr_err("\e[15;31m");
	ft_putstr(strerror(err));
	ft_putstr("\n");
	ft_putstr_err("\e[0m");
}
