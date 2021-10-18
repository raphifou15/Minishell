/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_after_parsing_2_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:19:37 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/18 00:50:18 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_value_inside_env(char *str2, t_env *begin, char *str3)
{
	t_env	*temp;

	temp = NULL;
	temp = begin;
	while (temp != NULL)
	{
		if (ft_strcmp(str2, temp->name) == 0)
			return (ft_strjoin(str3, temp->ctn));
		temp = temp->next;
	}
	if (str3 == NULL)
	{
		str3 = ft_calloc(sizeof(char), 1);
		if (str3 == NULL)
			str3 = '\0';
	}
	return (str3);
}

char	*find_value_from_env_or_interogation(char *str2, t_minishell *m,
			char *str3)
{	
	if (str2[0] == '$')
		return (ft_strjoin(str3, str2));
	if (str2[0] == '?')
		return (ft_strjoin(str3, "0"));
	return (ft_find_value_inside_env(str2, m->e, str3));
}

void	corrige_value(t_second_parse *begin)
{
	t_second_parse	*temp;

	temp = begin;
	while (temp != NULL)
	{
		if (temp->value == _DOLLAR)
			temp->value = EXP;
		if (strcmp(temp->str, "<<") == 0)
			temp->value = _R_INPUT_2;
		if (strcmp(temp->str, ">>") == 0)
			temp->value = _R_OUTPUT_2;
		temp = temp->next;
	}
}
