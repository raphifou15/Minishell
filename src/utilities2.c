/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <alebross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:43:59 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 02:42:31 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest != NULL && dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (src == NULL)
		return (dest);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;

	str = malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	nmemb = size * nmemb;
	while (nmemb > 0)
	{
		str[nmemb - 1] = 0;
		nmemb--;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		a;
	int		b;

	s3 = NULL;
	a = 0;
	b = 0;
	if (s1 == NULL)
		a = 0;
	else
		a = ft_strlen(s1);
	if (s2 == NULL)
		return (s1);
	b = ft_strlen(s2);
	s3 = ft_calloc(sizeof(char), a + b + 1);
	if (s3 == NULL)
		ft_free(s1);
	if (s3 == NULL)
		return (NULL);
	s3 = ft_strcpy(s3, s1);
	s3 = ft_strcat(s3, s2);
	ft_free(s1);
	return (s3);
}

char	*ft_join3(char *str1, char *str2, char *str3)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (str1 != NULL)
		i += ft_strlen(str1);
	if (str2 != NULL)
		i += ft_strlen(str2);
	if (str3 != NULL)
		i += ft_strlen(str3);
	str = ft_calloc(sizeof(char), i + 1);
	if (str == NULL)
		return (NULL);
	if (str1 != NULL)
		str = ft_strcpy(str, str1);
	if (str2 != NULL)
		str = ft_strcat(str, str2);
	if (str3 != NULL)
		str = ft_strcat(str, str3);
	return (str);
}

//ft_strjoin modif pour ne pas avoir de leak ni segfault
//il free a l'interieur de lui meme.
