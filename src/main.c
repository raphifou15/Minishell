/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:40:05 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/13 20:56:19 by alebross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_minishell *m, char **env)
{
	(void)env;
	m->p1 = NULL;
	m->p2 = NULL;
	m->use = 0;
	return (0);
}

void	destroy_all(t_minishell *m, char *line, int use)
{
	if (use == 0)
	{
		ft_free_all_the_list(m->p1);
		ft_free_all_the_list_2(m->p2);
		ft_free(line);
	}
	m->p1 = NULL;
	m->p2 = NULL;
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
		printf("%s\n", line);
		if (parsing_1(&m) != 0)
			m.use = (ft_free(line) + 1);
		if (m.use == 0 && parsing_2(&m) != 0)
			m.use = (ft_free_all_the_list(m.p1) + ft_free(line) + 1);
		if (ft_strcmp(rl_line_buffer, "bonjour") == 0)
			temp = 1;
		if (m.use == 0)
			printf("%s\n", line);
		destroy_all(&m, line, m.use);
		m.use = 0;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (minishell(env, "$>") != 0)
		return (1);
	return (0);
}
