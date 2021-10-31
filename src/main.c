/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:40:05 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/31 02:10:05 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_minishell *m, char **env)
{
	m->r.fd_out_save = -5;
	m->r.fd_out = -5;
	m->r.error = 0;
	m->r.i = 0;
	m->e = NULL;
	m->p1 = NULL;
	m->p2 = NULL;
	m->p3 = NULL;
	m->use = 0;
	if (add_env_variable_to_list(m, env) != 0)
		return (1);
	if (m->e == NULL)
		m->e = init_env(NULL, NULL);
	if (m->e == NULL)
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
			executing(m.p3, &m, line);
		if (m.use == 0 && ft_strcmp(line, "") == 1)
			add_history(line);
		if (m.use == 0 && ft_strcmp(line, "bonjour") == 0)
			temp = 1;
		reboot(&m, line);
	}
	ft_free_all_elem_env(m.e);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (minishell(env, "\e[11;34mMinishell$>\e[0m") != 0)
	{
		close(0);
		close(1);
		close(2);
		return (1);
	}
	close(0);
	close(1);
	close(2);
	return (0);
}

// init_minishell entierement verifier normalement renvoie juste checker les
// messages d'erreurs;

// ft_display_env_list(m.e);
//		if (m.use == 0)
//			printf("%s\n", line);

//	add_env_variable_to_list dans le fichier env.c
//	parsing1 verifier
