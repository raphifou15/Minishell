/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:29:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/08 01:54:46 by rkhelif          ###   ########.fr       */
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
	int						retour;
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

//	main.c
int				main(int argc, char **argv, char **env);
void			destroy_all(t_minishell *m, char *line, int use);
//
//	utilities1.c
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_err(char *str);
void			ft_putstr(char *str);
int				ft_strlen(char *str);
char			*ft_strdup(char *str);
//
//	utilities2.c
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dest, char *src);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_join3(char *str1, char *str2, char *str3);
//
//	utilities3.c
char			*ft_strchr(const char *s, int c);
int				ft_strchr2(const char *s, char c);
void			ft_putstr_fd(char *str, int fd);
int				ft_is_char(char c);
void			ft_atoi_modif(int num, char *str);
//
//	ft_free.c
int				ft_free(char *str);
char			*ft_free_null(char *str);
void			ft_free2(void *data);
int				ft_free_all_the_list(t_first_parse *begin);
int				ft_free_all_the_list_2(t_second_parse *begin);
//
//	ft_free2.c
int				ft_free_all_elem_env(t_env *begin);
char			**ft_free_double_tab(char **tab);
void			*ft_free3(void *data);
//
//	env.c
char			*put_inside_name(char *src);
char			*put_inside_ctn(char *src);
int				add_env_variable_to_list(t_minishell *m, char **env);
//
//	env2.c
int				ft_list_push_back_env_2(t_env **begin, char *name, char *ctn);
t_env			*create_elem_env(char *name, char *ctn);
t_env			*init_env(char *name, char *ctn);
//
//	parsing_1.c
int				find_the_good_value(char c);
t_first_parse	*ft_create_elem(char c, int b);
int				parsing_1(t_minishell *m);
//
//	checking_after_parsing_1.c
void			transform_value_for_dollar_inside_double_quote(
					t_first_parse **begin, int pivot);
void			transform_value_for_dollar(t_first_parse **begin);
void			transform_value_inside_quote(t_first_parse **begin);
int				check_quote_number(t_first_parse **begin);
int				check_multi_special_char(t_first_parse **begin,
					t_first_parse *temp);
//
//	checking_after_parsing_1_2.c
void			transform_value_for_dollar_exeption(t_first_parse **begin);
void			transform_value_for_dollar_exeption2(t_first_parse **begin);
void			transform_value_quote(t_first_parse **begin);
//
//	checking_after_parsing_1_3.c
void			transform_value_for_here_doc(t_first_parse **begin);
//
//	parsing_2.c
int				ft_list_push_back_2(t_second_parse **begin, t_first_parse *p1,
					int len);
t_second_parse	*ft_create_elem_2(t_first_parse *p1, int len);
int				next_parse_len(t_first_parse *begin);
int				parsing_2_part_0(t_minishell *m);
int				parsing_2(t_minishell *m);
//
//	checking_after_parsing_2.c
char			*find_name_value_to_transform(char *str, int len);
int				len_elem_until_dollar_or_end(char *str);
int				change_elem_dollar(t_second_parse *begin, t_minishell *m);
int				find_new_value_to_temp(t_second_parse *temp, char *str,
					t_minishell *m);
int				change_elem_dollar_part2(t_second_parse *temp, t_minishell *m);
//
//	checking_after_parsing_2_2.c
char			*find_value_from_env_or_interogation(char *str2, t_minishell *m,
					char *str3);
void			corrige_value(t_second_parse *begin);
void			corrige_value2(t_second_parse *begin);
//
//	parsing_3.c
int				ft_list_push_back_3(t_second_parse **begin,
					t_second_parse *temp);
t_second_parse	*ft_create_elem_3(t_second_parse *temp);
int				parsing_3_part_0(t_minishell *m);
int				parsing_3(t_minishell *m);
//
//	checking_after_parsing_3.c
void			change_next_value(t_second_parse *begin, int v);
void			delete_elem_inside_list(t_second_parse *begin, int be);
int				redirection(int value);
void			corrige_redirection(t_second_parse *begin, t_minishell *m);
int				check_error_syntax(t_second_parse *begin);
//
//	checking_after_parsing_3_2.c
int				check_if_list_is_ordered(t_second_parse *begin);
t_second_parse	*change_place_elem(t_second_parse *begin, t_minishell *m,
					int elem, int i);
void			order_list(t_second_parse *begin, t_minishell *m);
int				check_syntax_error_pipe(t_second_parse *begin);
void			corrige_empty_quote(t_second_parse *temp);
//	error1.c
int				error1(int err);
void			error2(int err);
//
//	display.c
void			display_elem(t_first_parse *begin);
void			display_elem_2(t_second_parse *begin);
void			ft_display_env_list(t_env *begin);
void			ft_display_export_list(t_env *begin);
//
//	exec_1.c
int				find_nbr_pipe(t_second_parse *begin);
void			child_process_whithout_pipe(t_second_parse *begin,
					t_minishell *m, char *line);
void			executing_without_pipe(t_second_parse *begin, t_minishell *m,
					char *line);
void			executing(t_second_parse *begin, t_minishell *m, char *line);
//
//	env_list_to_tab.c
int				nbr_line_inside_env(t_env *e);
char			**env_list_to_tab(t_env *e);
//
//	argv_list_to_tab.c
int				find_nbr_argv(t_second_parse *begin);
char			**argv_list_to_tab(t_second_parse *begin);
int				absolute_way(t_second_parse *begin);
//
//	free_inside_process_wihout_pipe.c
void			free_inside_process_without_pipe_1(char **env, t_minishell *m,
					char *line);
void			free_inside_process_without_pipe_2(char **argv, char **env,
					t_minishell *m, char *line);
void			free_inside_process_without_pipe_3(char **argv, char **env,
					t_minishell *m, char *line);
//
//	list_env_argv_to_tab.c
char			*find_elem_access(t_second_parse *begin, char **tab);
char			*way_of_path(t_env *env);
char			**list_env_argv_to_tab(t_second_parse *begin, t_env *env);
//
//	ft_split.c
char			**ft_split(const char *str, char c);
//
//	built_in.c
int				check_first_elem_echo(char *str);
void			built_in_echo(t_minishell *m, t_second_parse *begin);
void			built_in_env(t_env *env);
int				is_it_a_built_in(char *str);
void			make_a_built_in(t_second_parse *begin, t_minishell *m,
					char *line);
//
//	built_in_2.c
void			built_in_pwd(void);
void			delete_elem_env(t_env *begin, int be);
void			built_in_unset_2(t_env *tmp_env, t_env *env,
					t_minishell *m, int i);
void			built_in_unset(t_env *env, t_minishell *m,
					t_second_parse *begin, int i);
void			built_in_exit(t_minishell *m, t_second_parse *begin,
					char *line);
//
//	built_in_cd.c
void			built_in_cd(t_minishell *m, t_second_parse *begin);
//
//	built_in_export.c
void			built_in_export(t_minishell *m, t_second_parse *begin);
//
//	redirections_1.c
t_second_parse	*redirections(t_second_parse *begin, t_minishell *m,
					char *line);
//
//	redirections_2.c
void			close_fds_and_error(t_minishell *m);
int				find_nbr_out(t_second_parse *begin);
int				find_nbr_in(t_second_parse *begin);
void			init_redirection(t_minishell *m, char *line,
					t_second_parse *begin);
//
//	redirections_heredoc.c
void			write_in_herdoc(char *str, int fd2, t_minishell *m, int v);
//
//	close_and_reboot.c
void			reboot(t_minishell *m, char *line);
void			reboot_executing_with_pipe(t_minishell *m);
//
//	get_next_line_modif.c
int				get_next_line_modif(int fd, char **line);
//
//	exec_with_pipe.c
void			executing_with_pipe(t_second_parse *begin, t_minishell *m,
					char *line, int nbr_pipe);
//
//	redirections_heredoc_multi_pipes.c
int				find_nbr_heredoc(t_second_parse *temp);
void			init_heredoc_and_write_in_file(t_second_parse *begin,
					t_minishell *m, int nbr_pipe);
//
//	redirection_multipipes.c
void			redirections_multipipes(t_second_parse *temp, t_minishell *m);
//
//	free_inside_pipe_multi.c
void			free_child_proc_mult_doc_fail(t_minishell *m, char *line);
void			free_child_proc_mult_end(t_minishell *m, char *line, char **env,
					char **argv);
//
//	exec_with_pipe2.c
t_second_parse	*inside_parent_multi_pipe(t_second_parse *temp, t_minishell *m);
//
//	handler.c
void			handler_default(int nb);
void			handler_inside_child(int nb);
void			handler_heredoc(int nb);
//
//	redirections_heredoc_single_pipe.c
void			init_and_write_in_heredoc_single(t_second_parse *begin,
					t_minishell *m);
//
//	 wait.c
void			wait_without_pipe(t_minishell *m, pid_t pid);
//
//	signal.c
void			signal_begin(t_minishell *m, char *line);
void			signal_end(t_minishell *m);
void			signal_default(void);
//
#endif
