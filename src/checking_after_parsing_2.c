/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:57:03 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/13 18:04:04 by rkhelif          ###   ########.fr       */
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
	int		i;
	int		len;

	i = 0;
	while (temp->str[i] != '\0')
	{
		len = len_elem_until_dollar_or_end(temp->str + i);
		printf("len = %d\n", len);
		i += len;
	}
	return (1);
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
