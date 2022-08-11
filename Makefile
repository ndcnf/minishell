# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 11:41:15 by nchennaf          #+#    #+#              #
#    Updated: 2022/08/11 14:24:34 by nchennaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYN = \033[36m
YEL = \033[33m
GRN = \033[32m
RST = \033[0m

CC =	gcc
CFLAGS =	-Wall -Wextra -Werror -g #-fsanitize=address
NAME =	minishell
AR =	ar rcs
SRC =	src/builtins.c \
		src/main.c \
		src/b_export.c \
		src/env_utils.c \
		src/b_unset.c \

DIR_LIBFT = ./utils/libft/
LIB_LIBFT = ft
DIR_GNL = ./utils/get_next_line/
LIB_GNL = gnl
HEADER = -Iinc
DEL = rm -rf

OBJ =	${SRC:.c=.o}

all:	${NAME}

%.o:	%.c
		@${CC} ${CFLAGS} ${HEADER} -c $< -o $@
${NAME}:	${OBJ}
		@echo "[LIBFT]		${CYN}Creating...${RST}"
		@${MAKE} -C ${DIR_LIBFT}
		@echo "[LIBFT]		${GRN}OK${RST}"
		@echo "[GET NEXT LINE]	${CYN}Creating...${RST}"
		@${MAKE} -C ${DIR_GNL}
		@echo "[GET NEXT LINE]	${GRN}OK${RST}"
		@echo "[MINISHELL]	${CYN}Compilating...${RST}"
		@${CC} ${OBJ} ${CFLAGS} \
		-L${DIR_LIBFT} -l${LIB_LIBFT} \
		-L${DIR_GNL} -l${LIB_GNL} \
		-o ${NAME}
		@echo "[MINISHELL]	${GRN}OK${RST}"
exec:	all
		./${NAME}
norm:	all
		norminette ${SRC} minishell.h
clean:
			@echo "[MINISHELL]	${YEL}Deleting...${RST}"
			@${DEL} ${OBJ}
			@echo "[MINISHELL]	${GRN}Cleaned${RST}"
			@echo "[LIBFT]		${YEL}Deleting...${RST}"
			@${MAKE} -C ${DIR_LIBFT} clean
			@echo "[LIBFT]		${GRN}Cleaned${RST}"
			@echo "[GET NEXT LINE]	${YEL}Deleting...${RST}"
			@${MAKE} -C ${DIR_GNL} clean
			@echo "[GET NEXT LINE]	${GRN}Cleaned${RST}"

fclean:		clean
			@${DEL} ${NAME}
			@echo "${GRN}Cleaning complete.${RST}"

re:			fclean all

.PHONY:		all clean fclean