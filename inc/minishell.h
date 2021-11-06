/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:29:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/06 04:57:02 by rkhelif          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>

int				g_signal;

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

typedef struct s_redirection
{
	int						fd_out_save;
	int						fd_in_save;
	int						fd_out;
	int						fd_in;
	int						error;
	int						i;
	int						nbr_out;
	int						nbr_in;
}				t_redirection;

typedef struct s_multipipes
{
	int						pipefd[2];
	int						fd_in;
	pid_t					pid;
	int						*fds;
	int						i;
	int						j;
	int						nbr_h;
	int						nbr_p;
}				t_multipipes;

typedef struct s_single
{
	int						nbr_h;
	int						*fds;
	int						i;
	int						j;
}				t_single;

typedef struct s_minishell
{
	t_first_parse			*p1;
	t_second_parse			*p2;
	t_second_parse			*p3;
	t_env					*e;
	t_redirection			r;
	t_multipipes			mp;
	t_single				s;
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
# define _QUOTE_EMPTY	14
# define _DELIMITEUR_2	15

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
int				ft_is_char(char c);

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

t_env			*init_env(char *name, char *ctn);
t_env			*init_env2(t_env *env, char *name, char *ctn);
t_env			*init_env3(t_env *env, char *name, char *ctn);
t_env			*create_elem_env(char *name, char *ctn);
int				ft_list_push_back_env_2(t_env **begin, char *name, char *ctn);

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
void			transform_value_quote(t_first_parse **begin);

void			transform_value_for_here_doc(t_first_parse **begin);

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
void			corrige_empty_quote(t_second_parse *temp);

int				error1(int err);
void			error2(int err);

void			display_elem(t_first_parse *begin);
void			display_elem_2(t_second_parse *begin);
void			ft_display_env_list(t_env *begin);
void			ft_display_export_list(t_env *begin);

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
void			built_in_env(t_env *env);
void			built_in_pwd(void);
void			delete_elem_env(t_env *begin, int be);
void			built_in_unset(t_env *env, t_minishell *m,
					t_second_parse *begin, int i);
void			built_in_unset_2(t_env *tmp_env, t_env *env,
					t_minishell *m, int i);
int				check_first_elem_echo(char *str);
void			built_in_cd(t_minishell *m, t_second_parse *begin);
void			actualise_pwd(t_env *env);
void			actualise_oldpwd(t_env *env);
void			built_in_export(t_minishell *m, t_second_parse *begin);
void			built_in_export_2(t_env *env, char *str, char *name, char *ctn);
void			built_in_export_3(t_env *env, char *str);

t_second_parse	*redirections(t_second_parse *begin, t_minishell *m,
					char *line);
void			redirection_input2(t_minishell *m, t_second_parse *temp);

void			init_redirection(t_minishell *m, char *line,
					t_second_parse *begin);
int				find_nbr_out(t_second_parse *begin);
int				find_nbr_in(t_second_parse *begin);
void			close_fds_and_error(t_minishell *m);

void			write_in_herdoc(char *str, int fd2, t_minishell *m, int v);

void			reboot(t_minishell *m, char *line);
void			reboot_executing_with_pipe(t_minishell *m);

int				get_next_line_modif(int fd, char **line);

char			*ft_strchr(const char *s, int c);
int				ft_strchr2(const char *s, char c);
void			ft_putstr_fd(char *str, int fd);

void			executing_with_pipe(t_second_parse *begin, t_minishell *m,
					char *line, int nbr_pipe);

void			init_heredoc_and_write_in_file(t_second_parse *begin,
					t_minishell *m, int nbr_pipe);
int				find_nbr_heredoc(t_second_parse *temp);

void			redirections_multipipes(t_second_parse *temp, t_minishell *m);

void			free_child_proc_mult_doc_fail(t_minishell *m, char *line);
void			free_child_proc_mult_end(t_minishell *m, char *line, char **env,
					char **argv);
t_second_parse	*inside_parent_multi_pipe(t_second_parse *temp, t_minishell *m);

void			reboot_executing_with_pipe(t_minishell *m);

void			handler_default(int nb);
void			handler_inside_child(int nb);
void			handler_heredoc(int nb);

void			init_and_write_in_heredoc_single(t_second_parse *begin,
					t_minishell *m);
#endif
