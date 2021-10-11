/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:29:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/11 19:56:27 by alebross         ###   ########.fr       */
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

# define EXP			0
# define _SPACE			1
# define _QUOTE			2
# define _DOUBLE_QUOTE	3
# define _BACKSLASH		4
# define _SEMICOLON		5
# define _DOLLAR		6
# define _R_INPUT		7
# define _R_OUTPUT		8
# define _PIPE			9
# define _QUESTION		10

int				main(int argc, char **argv, char **env);
int				minishell(void);

int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_err(char *str);
void			ft_putstr(char *str);

int				ft_free(char *str);
void			ft_free2(void *data);
int				ft_free_all_the_list(t_first_parse *begin);

int				parsing_1(t_minishell *m);
int				parsing_1_part_0(t_minishell *m, int i);
t_first_parse	*ft_create_elem(char c, int b);
int				find_the_good_value(char c);
int				ft_list_push_back(t_first_parse **begin, char c, int b);

void			transform_value_inside_quote(t_first_parse **begin);
int     		check_quote_number(t_first_parse **begin);

int				error1(int err);

void			display_elem(t_first_parse *begin);
#endif
