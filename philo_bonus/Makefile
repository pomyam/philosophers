# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 19:02:54 by pyamcha           #+#    #+#              #
#    Updated: 2021/07/30 19:02:55 by pyamcha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = philo_bonus.c checkers_bonus.c dop_bonus.c inits_bonus.c

HEADERS = philo_bonus.h

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
