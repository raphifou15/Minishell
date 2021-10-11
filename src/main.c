/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:40:05 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/11 05:47:37 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(void)
{
	t_minishell	m;
	char		*prompt;
	char		*line;
	int			temp;

	temp = 0;
	prompt = NULL;
	line = NULL;
	m.p1 = NULL;
	while (temp == 0)
	{
		line = readline(prompt);
		if (parsing_1_part_0(&m, -1) != 0)
			return (ft_free(line) + 1);
		display_elem((&m)->p1);
		if (ft_strcmp(rl_line_buffer, "bonjour") == 0)
			temp = 1;
		printf("%s\n", line);
		ft_free_all_the_list((&m)->p1);
		ft_free(line);
		m.p1 = NULL;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	if (minishell() != 0)
		return (1);
	return (0);
}
