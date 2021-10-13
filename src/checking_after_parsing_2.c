/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:57:03 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/13 21:03:32 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_elem_until_dollar_or_end(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '\0') && (str[i] != '$' || i == 0))
		i++;
	return (i);
}

int	change_elem_dollar_part2(t_second_parse *temp)
{
	(void)temp;
	return (0);
}

int	change_elem_dollar(t_second_parse *begin)
{
	t_second_parse	*temp;

	temp = NULL;
	temp = begin;
	while (temp != NULL)
	{
		if (temp->value == _DOLLAR)
		{
			if (change_elem_dollar_part2(temp) != 0)
				return (1);
		}
		temp = temp->next;
	}
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

//	int		i;
//	int		len;
//	char	*str;
//	char	*str2;
//	char	*str3;
//
//	str = ft_strdup(temp->str);
//	free(temp->str);
//	temp->str = NULL;
//	i = 0;
//	while (str[i] != '\0')
//	{
//		len = len_elem_until_dollar_or_end(str + i);
//		str2 = malloc(sizeof(char) * len);
//		str2 = ft_strncpy(str2, str + i + 1, len -1);
//		str3 = getenv(str2);
//		printf("len = %d\nstr2 = %s\n", len, str2);
//		printf("str3 %s\n", str3);
//		i += len;
//		free(str2);
//		str2 = NULL;
//	}
