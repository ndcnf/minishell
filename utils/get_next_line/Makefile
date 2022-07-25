# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAkefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 11:50:12 by nchennaf          #+#    #+#              #
#    Updated: 2022/07/25 13:24:27 by nchennaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Werror -Wall -Wextra
NAME = libgnl.a
AR = ar rcs
SRC =	get_next_line.c \
		get_next_line_utils.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	@${AR} ${NAME} ${OBJ}

clean:
	@rm -rf ${OBJ}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean