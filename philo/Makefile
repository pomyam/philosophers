# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 19:02:28 by pyamcha           #+#    #+#              #
#    Updated: 2021/07/30 19:02:29 by pyamcha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c checkers.c dop.c inits.c

HEADERS = philo.h

OPTION = -c -I ${HEADER}

OBJS = ${patsubst %.c,%.o,${SRCS}}

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re