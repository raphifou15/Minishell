/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:46:47 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 04:03:49 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atol(char *str)
{
	long	i;
	long	sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if ((str[i] == '-' || str[i] == '+')
		&& (str[i + 1] >= '0' && str[i + 1] <= '9'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = 10 * nb + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL)
		return (s1 - s2);
	if (s2 == NULL)
		return (s1 - s2);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
