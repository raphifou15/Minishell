/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:29:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/19 20:32:29 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_second_parse
{
	int						value;
	char					*str;
	struct s_second_parse	*next;
}				t_second_parse;

typedef struct s_first_parse
{
	int						value;
	char					c;
	struct s_first_parse	*next;
}				t_first_parse;

typedef struct s_env
{
	char					*name;
	char					*ctn;
	struct s_env			*next;
}				t_env;

typedef struct s_minishell
{
	t_first_parse			*p1;
	t_second_parse			*p2;
	t_second_parse			*p3;
	t_env					*e;	
	int						use;
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
# define _R_INPUT_2		11
# define _R_OUTPUT_2	12

int				main(int argc, char **argv, char **env);
int				minishell(char **env, char *prompt);
void			destroy_all(t_minishell *m, char *line, int use);
int				init_minishell(t_minishell *m, char **env);
void			parsing(t_minishell *m, char *line);

int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_err(char *str);
void			ft_putstr(char *str);
int				ft_strlen(char *str);
char			*ft_strdup(char *str);

//char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strcat(char *dest, char *src);
char			*ft_strjoin(char *s1, char *s2);
void			*ft_calloc(size_t nmemb, size_t size);

int				ft_free(char *str);
char			*ft_free_null(char *str);
void			ft_free2(void *data);
int				ft_free_all_the_list(t_first_parse *begin);
int				ft_free_all_the_list_2(t_second_parse *begin);

int				ft_free_all_elem_env(t_env *begin);

int				add_env_variable_to_list(t_minishell *m, char **env);
int				ft_list_push_back_env(t_env **begin, char *str);
t_env			*ft_create_elem_env(char *str);
char			*put_inside_ctn(char *src);
char			*put_inside_name(char *src);

int				parsing_1(t_minishell *m);
int				parsing_1_part_0(t_minishell *m, int i);
t_first_parse	*ft_create_elem(char c, int b);
int				find_the_good_value(char c);
int				ft_list_push_back(t_first_parse **begin, char c, int b);

int				check_multi_special_char(t_first_parse **begin,
					t_first_parse *temp);
void			transform_value_inside_quote(t_first_parse **begin);
int				check_quote_number(t_first_parse **begin);
void			transform_value_for_dollar(t_first_parse **begin);
void			transform_value_for_dollar_inside_double_quote(
					t_first_parse **begin, int pivot);

void			transform_value_for_dollar_exeption(t_first_parse **begin);

int				parsing_2(t_minishell *m);
int				parsing_2_part_0(t_minishell *m);
t_second_parse	*ft_create_elem_2(t_first_parse *p1, int len);
int				ft_list_push_back_2(t_second_parse **begin, t_first_parse *p1,
					int len);
int				next_parse_len(t_first_parse *begin);

int				change_elem_dollar(t_second_parse *begin, t_minishell *m);
int				change_elem_dollar_part2(t_second_parse *temp, t_minishell *m);
void			corrige_value(t_second_parse *begin);
int				len_elem_until_dollar_or_end(char *str);
int				find_new_value_to_temp(t_second_parse *temp, char *str,
					t_minishell *m);
char			*find_name_value_to_transform(char *str, int len);

char			*find_value_from_env_or_interogation(char *str2, t_minishell *m,
					char *str3);

int				parsing_3(t_minishell *m);
int				parsing_3_part_0(t_minishell *m);
t_second_parse	*ft_create_elem_3(t_second_parse *temp);
int				ft_list_push_back_3(t_second_parse **begin,
					t_second_parse *temp);

int				error1(int err);

void			display_elem(t_first_parse *begin);
void			display_elem_2(t_second_parse *begin);
void			ft_display_env_list(t_env *begin);

void			executing(t_minishell *m);
#endif
