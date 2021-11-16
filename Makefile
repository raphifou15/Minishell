# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/10 18:33:31 by rkhelif           #+#    #+#              #
#    Updated: 2021/11/16 18:44:07 by alebross         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
RM = rm -rf
DIR_OBJ = other
DIR_SRC = src
DIR_INC = inc

SRCS = 	main.c \
		ft_split.c \
		utilities1.c \
		utilities2.c \
		utilities3.c \
		utilities4.c \
		ft_free.c \
		ft_free2.c \
		free_inside_process_wihout_pipe.c \
		free_inside_pipe_multi.c \
		env.c \
		env2.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		checking_after_parsing_1.c \
		checking_after_parsing_1_2.c \
		checking_after_parsing_1_3.c \
		checking_after_parsing_2.c \
		checking_after_parsing_2_2.c \
		checking_after_parsing_3.c \
		checking_after_parsing_3_2.c \
		exec_1.c \
		exec_with_pipe.c \
		exec_with_pipe2.c \
		error1.c \
		display.c \
		env_list_to_tab.c \
		argv_list_to_tab.c \
		list_env_argv_to_tab.c \
		redirections_1.c \
		redirections_2.c \
		redirections_heredoc.c \
		redirections_heredoc_multi_pipes.c \
		redirections_heredoc_single_pipe.c \
		built_in.c \
		built_in_cd.c \
		built_in_pwd.c \
		built_in_echo.c \
		built_in_export.c \
		built_in_export_2.c \
		built_in_exit.c \
		built_in_unset.c \
		built_in_env.c \
		close_and_reboot.c \
		redirection_multipipes.c \
		get_next_line_modif.c \
		good_return_multipipe.c \
		wait.c \
		signal.c \
		display_export.c \
		display_export_2.c \
		handler.c

OBJS = ${addprefix ${DIR_OBJ}/,${SRCS:.c=.o}}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -lreadline
all:${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME} -lreadline

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	[ -d $(DIR_OBJ) ] || mkdir -p $(DIR_OBJ)
	${CC} $(FLAGS) -I ${DIR_INC} -c $< -o $@

clean:
	${RM} ${OBJS}
	${RM} ${DIR_OBJ}

fclean : clean
	${RM} ${NAME}
re: fclean all

.PHONY: all clean fclean re

