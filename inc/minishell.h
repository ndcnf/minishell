/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:25:30 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/09 14:27:34 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include "../utils/get_next_line/get_next_line.h"

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
	char	**args; //une commande valide entree par le user
	char	*path; //chemin du programme, devra etre renomme en *path au lieu de path[256]
	int		n_args; //nombre d'arguments (peut etre pas indispensable plus tard)
	char	**env; //copie des valeurs de l'environnement
	int		n_env; //nombre de variables d'environnement
} t_builtins;

//builtins.c
int		b_echo(t_builtins *bs);
void	b_init(t_builtins *bs, int argc, char *argv[], char *envp[]);
int		b_pwd(t_builtins *bs);
int		b_cd(t_builtins *bs);
int		b_exit(t_builtins *bs);
int		b_env(t_builtins *bs);
int		b_export(t_builtins *bs);
// void	parse_env(t_builtins *bs);
char	**parse_env(char *s);
void	sort_env(t_builtins *bs);
void	parse_it(char *s); //soon obsolete ?
void	add_key(t_builtins *bs, int pos);
void	need_bigger_array(t_builtins *bs, char *key, char *val);
void	dup_array_to_env(t_builtins *bs, char **array);

#endif