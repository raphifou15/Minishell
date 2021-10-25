# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/10 18:33:31 by rkhelif           #+#    #+#              #
#    Updated: 2021/10/26 01:49:47 by rkhelif          ###   ########.fr        #
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
		ft_free.c \
		ft_free2.c \
		free_inside_process_wihout_pipe.c \
		env.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		checking_after_parsing_1.c \
		checking_after_parsing_1_2.c \
		checking_after_parsing_2.c \
		checking_after_parsing_2_2.c \
		checking_after_parsing_3.c \
		checking_after_parsing_3_2.c \
		exec_1.c\
		error1.c \
		display.c \
		env_list_to_tab.c \
		argv_list_to_tab.c \
		list_env_argv_to_tab.c

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
