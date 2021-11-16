/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:40:05 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/16 20:37:29 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static int	init_minishell(t_minishell *m, char **env)
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
	m->retour = 0;
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
	if (use == 0 || use == 2 || use == 3)
	{
		ft_free_all_the_list_2(m->p3);
		ft_free(line);
	}
	m->p1 = NULL;
	m->p2 = NULL;
	m->p3 = NULL;
}

static void	parsing(t_minishell *m, char *line)
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

static int	minishell(char **env, char *prompt)
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
		if (line != NULL && ft_strcmp(line, "") == 1)
			add_history(line);
		signal_begin(&m, line);
		parsing(&m, line);
		if (m.use == 0)
			executing(m.p3, &m, line);
		reboot(&m, line);
		signal_default();
		signal_end(&m);
	}
	ft_free_all_elem_env(m.e);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal_default();
	g_signal = 0;
	if (minishell(env, "Minishell$>") != 0)
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

//signal_default(void); signal.c;
//ne prend aucun paramettre, gere ctrl+c, ctrl\d;

//add_env_variable_to_list(t_minishell *m, char **env); env.c
//prend en paramettre la structure minishell et le double pointeur env;
//cette fonction a pour but de prendre les elements de env et de les mettre
//dans la liste chainne m.e;
// tous les mallocs et fonction de la lib on etait checker dans cette fonction

//init_env(char *, char *); env2.c;
//cette fonction prend en paramettre deux chaines NULL;
//Le but de la fonction est le meme que add_env_variable_to_list, si env vide;
//tous les mallocs et fonction de la lib on etait checker dans cette fonction;

//signal_begin(t_minishell *m, line) ; signal.c
//cette fonction a pour but de gerer le signal ctrl+d du debut et,
//transformer la valeur de $? en fonction du signal.
