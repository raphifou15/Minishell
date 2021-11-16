/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:06:16 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 19:06:17 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error1(int err)
{
	if (err == 0)
		ft_putstr_err("\e[15;31mError malloc failed\e[0m\n");
	else if (err == 1)
	{
		ft_putstr_err("\e[15;31mError syntax error (double ");
		ft_putstr_err("quote or simple quote are not close)\e[0m\n");
	}
	else if (err == 2)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `||'\e[0m\n");
	else if (err == 3)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `<<<'\e[0m\n");
	else if (err == 4)
		ft_putstr_err("\e[15;31mError syntax error (invalid redirection)\e[0m\n");
	else if (err == 5)
		ft_putstr_err("\e[15;31mCommand not found\e[0m\n");
	else if (err == 6)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `>>>'\e[0m\n");
	else if (err == 7)
		ft_putstr_err("\e[15;31msyntax error near unexpected token `|'\e[0m\n");
	return (0);
}

void	error2(int err)
{
	ft_putstr_err("\e[15;31m");
	ft_putstr_err(strerror(err));
	ft_putstr_err("\n");
	ft_putstr_err("\e[0m");
}

void	error3(char *str)
{
	ft_putstr_err("\e[15;31m");
	ft_putstr_err(str);
	ft_putstr_err(": command not found");
	ft_putstr_err("\n");
	ft_putstr_err("\e[0m");
}

void	error4(char *str)
{
	ft_putstr_err("\e[15;31m");
	ft_putstr_err(str);
	ft_putstr_err("\n");
	ft_putstr_err("\e[0m");
}

char	*error5(char *str)
{
	ft_putstr_err("\e[15;31m");
	ft_putstr_err(str);
	ft_putstr_err("\n");
	ft_putstr_err("\e[0m");
	return (NULL);
}
