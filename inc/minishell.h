/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:25:30 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/08 16:30:54 by mthiesso         ###   ########.fr       */
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
# define NEW_VAL 1
# define NO_VAL 2
# define CREATE_KEY 3

// structure minimale pour gerer les donnees pour tester les builtins
// sera certainement vouee a modification suite au parsing
typedef struct s_builtins
{
	char	*content;
	int		len;
	char	**args; //une commande valide entree par le user
	char	*path; //chemin du programme, devra etre renomme en *path au lieu de path[256]
	int		n_args; //nombre d'arguments (peut etre pas indispensable plus tard)
	char	**env; //copie des valeurs de l'environnement
	int		n_env; //nombre de variables d'environnement
	char	*file; // "test.txt"; //le nom d'un fichier entré, devra dispraitre au profit du parsing
}	t_builtins;

// structure des listes chaînées afin de pouvoir stocker les arguments
//et de pouvoir les utiliser de manière optimisée
typedef struct s_elem
{
	char				**content;
}	t_elem;

typedef struct s_input
{
	char				**content;
	int					nb_cmd;
	int					nb_elem;
	t_elem				*elem;
}	t_input;

//builtins.c
int		b_pwd(t_builtins *bs);
int		b_cd(t_builtins *bs);
int		b_exit(t_builtins *bs);
int		b_env(t_builtins *bs);

//parsing.c
void	parsing_init(char *args, t_input *input);
char	*parse_cmd(t_input *input, char *s);
int		check_quotes(t_input *input, char *s);

void	dividing_args(t_builtins *bs);
int		parse_pwd(t_builtins *bs, char *in);
int		skip_spaces(char *s, int i);
void	space_counter(t_input *input, char *s);
int		first_elem(t_input *input, char *s, char c);
int		d_quotes_mgmt(t_input *input, char *s, int i, int n);
int		s_quotes_mgmt(t_input *input, char *s, int i, int n);
int		no_quote_mgmt(t_input *input, char *s, int i, int n);
void	parsing_elem(t_input *input, char *s);
void	malloc_checker(char *s);

//env_utils.c
char	**parse_env(char *s);
void	sort_env(t_builtins *bs);
void	print_env(char **elem);
void	dup_array_to_env(t_builtins *bs, char **array);
void	freearray(char **m, int n);

//b_export.c
int		b_export(t_builtins *bs);
char	*get_key(t_builtins *bs, int pos);
char	*get_val(t_builtins *bs, int pos);
void	add_key(t_builtins *bs, char *key, char *val);
char	*define_val(char *key, char *val);

//b_unset.c
int		b_unset(t_builtins *bs);
void	remove_key(t_builtins *bs, char *key);

//b_echo.c
void	print_echo_n(t_builtins *bs, int i);
int		b_echo(t_builtins *bs);

//b_init.c
void	b_init(t_builtins *bs, int argc, char *argv[], char *envp[]);
void	malloc_checker(char *s);

//var.c
void	conv_var(t_builtins *bs);

//redirections.c
// void	redir_input(t_builtins *bs);
// void	redir_output(t_builtins *bs);
// void	append_in(t_builtins *bs);
// void	heredoc(t_builtins *bs);

#endif
