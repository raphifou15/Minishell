/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:15:02 by alebross          #+#    #+#             */
/*   Updated: 2021/11/16 20:18:01 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static long	exit_arg(char *arg, long *n)
{
	int	i;

	i = 0;
	if (arg[0] == '-')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_putstr_err("minishell: exit: ");
			ft_putstr_err(arg);
			ft_putstr_err(": numeric argument required\n");
			*n = 2;
			return (0);
		}
		i++;
	}
	*n = ft_atol(arg);
	return (1);
}

static long	exit_arg_2(char *arg, long *n)
{
	int	i;

	i = 0;
	if (arg[0] == '-')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_putstr_err("minishell: exit: ");
			ft_putstr_err(arg);
			ft_putstr_err(": numeric argument required\n");
			*n = 2;
			return (0);
		}
		i++;
	}
	*n = ft_atol(arg);
	return (1);
}

void	built_in_exit(t_minishell *m, t_second_parse *begin, char *line)
{
	t_second_parse	*temp;
	long			n;
	int				o;

	temp = begin->next;
	n = 0;
	if (temp != NULL)
		o = exit_arg(begin->next->str, &n);
	if (temp != NULL && temp->next != NULL)
	{
		if (o == 1)
		{
			ft_putstr_err("minishell: exit: too many arguments\n");
			return ;
		}
	}
	reboot(m, line);
	ft_free_all_elem_env(m->e);
	ft_putstr("exit\n");
	close(0);
	close(1);
	close(2);
	exit((char)n);
}

void	built_in_exit2(t_minishell *m, t_second_parse *begin, char *line)
{
	t_second_parse	*temp;
	long			n;
	int				o;

	(void)line;
	temp = begin->next;
	n = 0;
	if (temp != NULL)
		o = exit_arg_2(begin->next->str, &n);
	if (temp != NULL && temp->next != NULL)
	{
		if (o == 1)
		{
			ft_putstr_err("minishell: exit: too many arguments\n");
			m->retour = 2;
			return ;
		}
	}
	m->retour = n;
	ft_putstr("exit\n");
	return ;
}
