# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 11:41:15 by nchennaf          #+#    #+#              #
#    Updated: 2022/07/25 14:25:40 by nchennaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYN = \033[36m
YEL = \033[33m
GRN = \033[32m

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
		@echo "${CYN}[LIBFT]		Creating..."
		@${MAKE} -C ${DIR_LIBFT}
		@echo "${GRN}[LIBFT]		OK"
		@echo "${CYN}[GET NEXT LINE]	Creating ..."
		@${MAKE} -C ${DIR_GNL}
		@echo "${GRN}[GET NEXT LINE]	OK"
		@echo "${CYN}[MINISHELL]	Compilating..."
		@${CC} ${OBJ} ${FLAGS} \
		-L${DIR_LIBFT} -l${LIB_LIBFT} \
		-L${DIR_GNL} -l${LIB_GNL} \
		-o ${NAME}
		@echo "${GRN}[MINISHELL]	OK"
exec:	all
		./${NAME}
norm:	all
		norminette ${SRC} minishell.h
clean:
			@echo "${YEL}[MINISHELL]	Deleting..."
			@${DEL} ${OBJ}
			@echo "${GRN}[MINISHELL]	Cleaned"
			@echo "${YEL}[LIBFT]		Deleting..."
			@${MAKE} -C ${DIR_LIBFT} clean
			@echo "${GRN}[LIBFT]		Cleaned"
			@echo "${YEL}[GET NEXT LINE]	Deleting..."
			@${MAKE} -C ${DIR_GNL} clean
			@echo "${GRN}[GET NEXT LINE]	Cleaned"

fclean:		clean
			@${DEL} ${NAME}
			@echo "${GRN}Cleaning complete."

re:			fclean all

.PHONY:		all clean fclean