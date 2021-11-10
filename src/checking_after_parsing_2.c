/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:57:03 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/10 17:46:17 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_name_value_to_transform(char *str, int len)
{
	char	*str2;
	int		i;

	str2 = NULL;
	i = 0;
	if (len == 1)
	{
		str2 = malloc(sizeof(char) + 1);
		if (str2 == NULL)
			return (NULL);
		str2[0] = '$';
		str2[1] = '\0';
		return (str2);
	}
	str2 = malloc(sizeof(char) * len);
	if (str2 == NULL)
		return (NULL);
	while (++i < len)
		str2[i - 1] = str[i];
	str2[i - 1] = '\0';
	return (str2);
}

int	len_elem_until_dollar_or_end(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '\0') && (str[i] != '$' || i == 0))
		i++;
	return (i);
}

int	change_elem_dollar(t_second_parse *begin, t_minishell *m)
{
	t_second_parse	*temp;

	temp = NULL;
	temp = begin;
	while (temp != NULL)
	{
		if (temp->value == _DOLLAR)
		{
			if (change_elem_dollar_part2(temp, m) != 0)
			{
				m->retour = 1;
				return (1);
			}
			temp->value = EXP;
		}
		temp = temp->next;
	}
	return (0);
}

int	find_new_value_to_temp(t_second_parse *temp, char *str, t_minishell *m)
{
	int		i;
	int		len;
	char	*str2;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		str2 = NULL;
		len = len_elem_until_dollar_or_end(str + i);
		str2 = find_name_value_to_transform(str + i, len);
		if (str2 == NULL)
			return (error1(0) + 1);
		temp->str = find_value_from_env_or_interogation(str2, m, temp->str);
		if (temp->str == NULL)
			return (ft_free(str2) + error1(0) + 1);
		ft_free(str2);
		i += len;
	}
	return (0);
}

int	change_elem_dollar_part2(t_second_parse *temp, t_minishell *m)
{
	char	*str;

	str = NULL;
	str = ft_strdup(temp->str);
	if (str == NULL)
		return (error1(0) + 1);
	free(temp->str);
	temp->str = NULL;
	if (find_new_value_to_temp(temp, str, m) != 0)
		return (ft_free(str) + 1);
	free(str);
	str = NULL;
	return (0);
}

//faire une boucle a l'interieure de la fonction change_elem_dollar_part2
//le but est de prendre les bonnes valeurs stocker dans les dollars
//et de les stocker a l'interrieur temp->str
//utiliser la fonction getenv(char *str) pour recup les donnees
//reflexion sur la donner recup dans un premier temp le str total pour pouvoir
//free temp->str directement et avoir quelque chose de plus simple a
//manipuler.

//etape 1: str = temp->str;
//etape 2: free(temp->str); temp->str = NULL;
//etape 3: boucle str n'est pas finnis;
//etape 4: calcule de la longueur du dollar jusquau prochain.
//etape 5: str2 recup de la longeur du dollar;
//etape 6: Mettre dans str2 les valeur de str(longeur);
//etape 7: dans une fonction genten(*str2);
//etape 8: join temp->str str que renvoie get_env;

//	temp->str = ft_free_null(temp->str);
//	i = 0;
//	str2 = NULL;
//	while (str[i] != '\0')
//	{
//		len = len_elem_until_dollar_or_end(str + i);
//		str2 = malloc(sizeof(char) * len);
//		str2 = ft_strncpy(str2, str + i + 1, len - 1);
//		if (temp->str == NULL)
//			temp->str = ft_strdup(str2);
//		else
//			temp->str = ft_strjoin(temp->str, str2);
//		i += len;
//		str2 = ft_free_null(str2);
//	}
//	printf("temp->str=%s\n", temp->str);
//	str = ft_free_null(str);
