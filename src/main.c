/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:40:05 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/24 02:34:53 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_minishell *m, char **env)
{
	m->e = NULL;
	m->p1 = NULL;
	m->p2 = NULL;
	m->p3 = NULL;
	m->use = 0;
	if (add_env_variable_to_list(m, env) != 0)
		return (1);
	return (0);
}

void	destroy_all(t_minishell *m, char *line, int use)
{
	if (use == 0)
	{
		ft_free_all_the_list_2(m->p3);
		ft_free(line);
	}
	m->p1 = NULL;
	m->p2 = NULL;
	m->p3 = NULL;
}

void	parsing(t_minishell *m, char *line)
{
	if (parsing_1(m) != 0)
		m->use = (ft_free(line) + 1);
	if (m->use == 0 && parsing_2(m) != 0)
		m->use = (ft_free_all_the_list(m->p1) + ft_free(line) + 1);
	if (m->use == 0 && parsing_3(m) != 0)
		m->use = (ft_free_all_the_list(m->p1) + ft_free_all_the_list_2(m->p2)
				+ ft_free(line) + 1);
	if (m->use == 0)
		m->use = ft_free_all_the_list(m->p1) + ft_free_all_the_list_2(m->p2);
}

int	minishell(char **env, char *prompt)
{
	t_minishell	m;
	char		*line;
	int			temp;

	temp = 0;
	line = NULL;
	if (init_minishell(&m, env) != 0)
		return (1);
	while (temp == 0)
	{
		line = readline(prompt);
		parsing(&m, line);
		if (m.use == 0)
			executing(m.p3, &m);
		if (ft_strcmp(rl_line_buffer, "") == 1)
			add_history(rl_line_buffer);
		if (ft_strcmp(rl_line_buffer, "bonjour") == 0)
			temp = 1;
		if (m.use == 0)
			printf("%s\n", line);
		destroy_all(&m, line, m.use);
		m.use = 0;
	}
	ft_free_all_elem_env(m.e);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (minishell(env, "\e[11;34mMinishell$>\e[0m") != 0)
		return (1);
	return (0);
}

// ft_display_env_list(m.e);
