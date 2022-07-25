# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 11:41:15 by nchennaf          #+#    #+#              #
#    Updated: 2022/07/25 12:23:53 by nchennaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	gcc
FLAGS =	-Wall -Wextra -Werror #-g -fsanitize=address
NAME =	minishell
AR =	ar rcs
SRC =	src/builtins.c \
		src/main.c \

DIR_LIBFT = ./utils/libft/
LIB_LIBFT = ft
DIR_GNL = ./utils/get_next_line/
LIB_GNL = gnl
HEADER = -Iinc
DEL = rm -rf

OBJ =	${SRC:.c=.o}

all:	${NAME}

%.o:	%.c
		@${CC} ${FLAGS} ${HEADER} -c $< -o $@
${NAME}:	${OBJ}
		${MAKE} -C ${DIR_LIBFT}
		${MAKE} -C ${DIR_GNL}
		${CC} ${OBJ} ${FLAGS} \
		-L${DIR_LIBFT} -l${LIB_LIBFT} \
		-L${DIR_GNL} -l${LIB_GNL} \
		-o ${NAME}
exec:	all
		./${NAME}
norm:	all
		norminette ${SRC} minishell.h
clean:
			${DEL} ${OBJ}
			${MAKE} -C ${DIR_LIBFT} clean
			${MAKE} -C ${DIR_GNL} clean

fclean:		clean
			${DEL} ${NAME}

re:			fclean all

.PHONY:		all clean fclean