/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:29:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/26 18:58:51 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

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
# define _DELIMITEUR	13

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
char			*ft_join3(char *str1, char *str2, char *str3);

int				ft_free(char *str);
char			*ft_free_null(char *str);
void			ft_free2(void *data);
int				ft_free_all_the_list(t_first_parse *begin);
int				ft_free_all_the_list_2(t_second_parse *begin);

int				ft_free_all_elem_env(t_env *begin);
char			**ft_free_double_tab(char **tab);

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
void			transform_value_for_dollar_exeption2(t_first_parse **begin);

int				parsing_2(t_minishell *m);
int				parsing_2_part_0(t_minishell *m);
t_second_parse	*ft_create_elem_2(t_first_parse *p1, int len);
int				ft_list_push_back_2(t_second_parse **begin, t_first_parse *p1,
					int len);
int				next_parse_len(t_first_parse *begin);

int				change_elem_dollar(t_second_parse *begin, t_minishell *m);
int				change_elem_dollar_part2(t_second_parse *temp, t_minishell *m);
void			corrige_value(t_second_parse *begin);
void			corrige_value2(t_second_parse *begin);
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

int				check_error_syntax(t_second_parse *begin);
void			corrige_redirection(t_second_parse *begin, t_minishell *m);
int				redirection(int value);
void			delete_elem_inside_list(t_second_parse *begin, int be);
void			change_next_value(t_second_parse *begin, int v);

void			order_list(t_second_parse *begin, t_minishell *m);
int				check_if_list_is_ordered(t_second_parse *begin);
t_second_parse	*change_place_elem(t_second_parse *begin, t_minishell *m,
					int elem, int i);
int				check_syntax_error_pipe(t_second_parse *begin);

int				error1(int err);
void			error2(int err);

void			display_elem(t_first_parse *begin);
void			display_elem_2(t_second_parse *begin);
void			ft_display_env_list(t_env *begin);

void			executing(t_second_parse *begin, t_minishell *m, char *line);
int				find_nbr_pipe(t_second_parse *begin);
void			executing_without_pipe(t_second_parse *begin, t_minishell *m,
					char *line);
void			child_process_whithout_pipe(t_second_parse *begin,
					t_minishell *m, char *line);

char			**env_list_to_tab(t_env *e);
int				nbr_line_inside_env(t_env *e);

char			**argv_list_to_tab(t_second_parse *begin);
int				find_nbr_argv(t_second_parse *begin);
int				absolute_way(t_second_parse *begin);

void			free_inside_process_without_pipe_1(char **env, t_minishell *m,
					char *line);
void			free_inside_process_without_pipe_2(char **argv, char **env,
					t_minishell *m, char *line);
void			free_inside_process_without_pipe_3(char **argv, char **env,
					t_minishell *m, char *line);

char			**list_env_argv_to_tab(t_second_parse *begin, t_env *env);
char			*way_of_path(t_env *env);
char			*find_elem_access(t_second_parse *begin, char **tab);

char			**ft_split(const char *str, char c);

int				is_it_a_built_in(char *str);
void			make_a_built_in(t_second_parse *begin, t_minishell *m,
					char *line);
void			built_in_echo(t_second_parse *begin);
int				check_first_elem_echo(char *str);

#endif
