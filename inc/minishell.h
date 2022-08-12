/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlene <marlene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:25:30 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/12 17:19:05 by marlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>	// readline, rl*
# include <readline/history.h>	// readline, rl*
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <sys/stat.h>			// stat, lstat, fstat
# include <sys/ioctl.h>			// ioctl
# include <sys/types.h>			// read
# include <sys/uio.h>			// read
# include <signal.h>			// signal, sigaction, sig*, kill
# include <dirent.h>			// *dir
# include <string.h>			// strerror
# include <termios.h>			// tc*
# include <curses.h>			// tg*
# include <term.h>				// tg*
# include <fcntl.h>				// open

# define MAX_PATH 1024

// structure minimale pour gerer les donnees pour tester les builtins
// sera certainement vouee a modification suite au parsing
typedef struct s_builtins
{
	char	*content;
	char	**args; //une commande valide entree par le user
	char	*path; //chemin du programme, devra etre renomme en *path au lieu de path[256]
	int		n_args; //nombre d'arguments (peut etre pas indispensable plus tard)
	char	**env; //copie des valeurs de l'environnement
	int		n_env; //nombre de variables d'environnement
} t_builtins;

// structure des listes chaînées afin de pouvoir stocker les arguments 
//et de pouvoir les utiliser de manière optimisée
typedef struct s_cmd
{
	char				*content;
	struct cmd			*next;
	int					line;
} t_cmd;

typedef	struct	s_input
{
	char				*content;
	struct input		*next;
	int					line;
} t_input;

//builtins.c
int		b_echo(t_builtins *bs);
void	b_init(t_builtins *bs, int argc, char *argv[], char *envp[]);
int		b_pwd(t_builtins *bs);
int		b_cd(t_builtins *bs);
int		b_exit(t_builtins *bs);
int		b_env(t_builtins *bs);

//parsing.c
void	parsing_init(char *args, t_input *input);
void	dividing_args(t_builtins *bs);
int		parse_cmd(char *in);

#endif