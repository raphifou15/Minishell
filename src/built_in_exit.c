/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:15:02 by alebross          #+#    #+#             */
/*   Updated: 2021/11/11 19:44:09 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_in_exit_2(t_minishell *m, char *arg, char *line)
{
	long	n;

	n = 0;
	if (arg[0] == '-')
		n++;
	while (arg[n] != '\0')
	{
		if (arg[n] < '0' || arg[n] > '9')
		{
			ft_putstr_err("minishell: exit: ");
			ft_putstr_err(arg);
			ft_putstr_err(": numeric argument required\n");
			return ;
		}
		n++;
	}
	n = ft_atol(arg);
	reboot(m, line);
	ft_free_all_elem_env(m->e);
	close(0);
	close(1);
	close(2);
	exit(n);
}

void	built_in_exit(t_minishell *m, t_second_parse *begin, char *line)
{
	t_second_parse	*temp;
	long			n;

	temp = begin;
	n = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		n++;
	}
	if (n > 2)
	{
		ft_putstr_err("bash: exit: too many arguments\n");
		return ;
	}
	built_in_exit_2(m, begin->next->str, line);
}
