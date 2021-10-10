/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:29:07 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/10 21:40:33 by rkhelif          ###   ########.fr       */
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
	int						elem;
	struct s_first_parse	*next;
}				t_first_parse;

typedef struct s_minishell
{
	t_first_parse	*p1;
}				t_minishell;

# define EXP 0

int		main(int argc, char **argv, char **env);
int		minishell(void);

int		ft_strcmp(char *s1, char *s2);

int		ft_free(char *str);

int		parsing_1_part_0(int i);
#endif
