/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:29:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/11 03:02:28 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_first_parse
{
	int						value;
	char					c;
	struct s_first_parse	*next;
}				t_first_parse;

typedef struct s_minishell
{
	t_first_parse	*p1;
}				t_minishell;

# define EXP 0

int				main(int argc, char **argv, char **env);
int				minishell(void);

int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_err(char *str);

int				ft_free(char *str);
void			ft_free2(void *data);
int				ft_free_all_the_list(t_first_parse *begin);

int				parsing_1_part_0(t_minishell *m, int i);
t_first_parse	*ft_create_elem(char c, int b);
int				find_the_good_value(char c);
int				ft_list_push_back(t_first_parse **begin, char c, int b);

int				error1(int err);
#endif
