# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/10 18:33:31 by rkhelif           #+#    #+#              #
#    Updated: 2021/10/11 05:36:07 by rkhelif          ###   ########.fr        #
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
		utilities1.c \
		ft_free.c \
		parsing_1.c \
		error1.c \
		display.c

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
