/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:53:16 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/12 18:34:54 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen2(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && str[i] != c)
		;
	return (i);
}

static int	go_to_new_line(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && str[i] != c)
		;
	if (str[i] == c)
	{
		while (str[i] == c)
			i++;
	}
	return (i);
}

static char	*malloc_line(const char *str, char c)
{
	int		size;
	char	*str2;
	int		i;

	i = -1;
	size = ft_strlen2(str, c);
	str2 = (char *)malloc(sizeof(char) * (size + 1));
	if (str2 == NULL)
		return (NULL);
	while (str[++i] != '\0' && str[i] != c)
		str2[i] = str[i];
	str2[i] = '\0';
	return (str2);
}

static int	ft_lines(const char *str, char c)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] != '\0' && str[i] == c)
		i++;
	if (str[i] != '\0')
		nbr = 1;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			nbr++;
			while (str[i] == c)
				i++;
		}
		else
			i++;
	}
	while (--i > -1 && str[i] == c)
		;
	if (str[i + 1] != '\0')
		nbr--;
	return (nbr);
}

char	**ft_split(const char *str, char c)
{
	char	**tab;
	int		nbr_lines;
	int		x;
	int		i;

	i = 0;
	x = -1;
	tab = NULL;
	nbr_lines = ft_lines(str, c);
	tab = malloc(sizeof(tab[0]) * (nbr_lines + 1));
	if (tab == NULL)
		return (NULL);
	while (++x < nbr_lines && str[i] != '\0')
	{
		tab[x] = malloc_line(str + i, c);
		if (tab[x] == NULL)
			return (ft_free_double_tab(tab));
		i += go_to_new_line(str + i, c);
	}
	tab[x] = NULL;
	return (tab);
}
