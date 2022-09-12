# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 11:41:15 by nchennaf          #+#    #+#              #
#    Updated: 2022/09/12 10:36:55 by mthiesso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYN = \033[36m
YEL = \033[33m
GRN = \033[32m
RST = \033[0m

CC =	gcc
CFLAGS =	-Wall -Wextra -Werror -g -fsanitize=address
NAME =	minishell
AR =	ar rcs
SRC =	src/builtins.c \
		src/main.c \
		src/b_export.c \
		src/env_utils.c \
		src/b_unset.c \
		src/parsing.c \
		src/parsing_utils.c \
		src/b_echo.c \
		src/b_init.c \
		src/redirections.c \
		src/quotes_mgmt.c \
		src/var.c \

RL_V	:= $(shell brew list --versions  readline | sed 's/.*[[:blank:]]//')
RL_P	:= $(shell brew --cellar readline)
RL		= $(RL_P)/$(RL_V)
LIBS	= -L $(RL)/lib/ -lreadline -lhistory
INC		= -I. -I $(RL)/include/
DIR_LIBFT = ./utils/libft/
LIB_LIBFT = ft
HEADER = -I./inc
DEL = rm -rf

OBJ =	${SRC:.c=.o}

all:	${NAME}

%.o:	%.c
			@${CC} ${CFLAGS} ${HEADER} ${INC}  -c $< -o $@
${NAME}:	${OBJ}
			@echo "[LIBFT]		${CYN}Creating...${RST}"
			@${MAKE} -C ${DIR_LIBFT}
			@echo "[LIBFT]		${GRN}OK${RST}"
			@echo "[MINISHELL]	${CYN}Compilating...${RST}"
			@${CC} ${OBJ} ${CFLAGS} ${LIBS}\
			-L${DIR_LIBFT} -l${LIB_LIBFT}\
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

fclean:		clean
			@${DEL} ${NAME}
			@echo "${GRN}Cleaning complete.${RST}"

re:			fclean all

.PHONY:		all clean fclean
