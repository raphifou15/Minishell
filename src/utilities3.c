/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:55:23 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 02:38:36 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

int	ft_strchr2(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
		i++;
	write(fd, str, i);
}

int	ft_is_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

void	ft_atoi_modif(int num, char *str)
{
	int		count;
	long	num2;

	num2 = (long)num;
	count = 0;
	while (num > 9)
	{
		count++;
		num /= 10;
	}
	while (count >= 0)
	{
		str[count] = ((num2 % 10) + 48);
		num2 /= 10;
		count--;
	}
}
