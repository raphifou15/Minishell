/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:57:34 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/06 04:57:14 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (find_the_good_value(s1[i]) != EXP)
		return (0);
	if (s1[i] == '!' || s1[i] == '?')
		return (0);
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}

void	ft_check_and_write_what_inside_dollar(char *str, t_env *env, int fd2)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (special_strcmp(str, temp->name) == 0)
		{
			ft_putstr_fd(temp->ctn, fd2);
			return ;
		}
		temp = temp->next;
	}
}

int	next_dollar_value(char *str)
{
	int	i;

	i = 0;
	i++;
	while (str[i] != '\0')
	{
		if (find_the_good_value(str[i]) != EXP)
			return (i);
		if (str[i] == '!' || str[i] == '?')
			return (i);
		i++;
	}
	return (i);
}

void	write_in_herdoc(char *str, int fd2, t_minishell *m, int v)
{
	int	i;

	i = 0;
	if (v == _DELIMITEUR_2)
		ft_putstr_fd(str, fd2);
	while (v != _DELIMITEUR_2 && str != NULL && str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '$'
			&& str[i + 1] != 32 && (str[i + 1] < 9 || str[i + 1] > 13))
		{
			ft_check_and_write_what_inside_dollar(str + i + 1, m->e, fd2);
			i += next_dollar_value(str + i);
		}
		else
		{
			write(fd2, &str[i], 1);
			i++;
		}
	}
	ft_putstr_fd("\n", fd2);
}
