/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:25:30 by nchennaf          #+#    #+#             */
/*   Updated: 2022/09/29 13:23:54 by nchennaf         ###   ########.fr       */
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
# define NO_RESULT -1

# define ERR_PERM 126
# define ERR_404 127
# define ERR_SIGN 128
# define ERR_EXIT 255

# define OPT_IGN "Option(s) ignored\n"
# define ERR_ARG "Argument invalid in this scope\n"
# define ERR_NO_ARG "No argument(s) provided\n"
# define CMD_404 "command not found\n"
# define TM_ARG "too many arguments\n"
# define HOMELESS "HOME not set\n"

// structure minimale pour gerer les donnees pour tester les builtins
// sera certainement vouee a modification suite au parsing
// typedef struct s_builtins
// {
// 	char	*content;
// 	int		len;
// 	char	**args; //une commande valide entree par le user
// 	//char	*path; //chemin du programme, devra etre renomme en *path au lieu de path[256]
// 	int		n_args; //nombre d'arguments (peut etre pas indispensable plus tard)
// 	char	**env; //copie des valeurs de l'environnement
// 	int		n_env; //nombre de variables d'environnement
// 	char	*file; // "test.txt"; //le nom d'un fichier entré, devra dispraitre au profit du parsing
// }	t_builtins;

// int		g_exit_stat; // ------------------------------------------------------ declarer une variable globale

// structure des listes chaînées afin de pouvoir stocker les arguments
//et de pouvoir les utiliser de manière optimisée
typedef struct s_elem
{
	char				**cont;
}	t_elem;

typedef struct s_input
{
	char				*cont;
	int					n_elem;
	t_elem				*elem;
	int					fd;
}	t_input;

typedef struct s_data
{
	char				**env;
	int					n_env;
	char				*path;
	int					n_cmd;
	t_input				*in;
}	t_data;

//prompt.c
void	prompt(char **envp);

//builtins.c
int		b_pwd(t_data *dt);
int		b_exit(t_data *dt, int in);
int		b_env(t_data *dt);

//builtins_selector.c
void	cmd_selector(t_data *dt, int i);

//parsing.c
void	parsing_init(char *args, t_data *dt);
char	*parse_cmd(t_data *dt, char *s, int in);
// void	dividing_args(t_builtins *bs); // ---------------------------------------- utile ou non ?
// int		parse_pwd(t_builtins *bs, char *in); // ------------------------------ utile ou non ?
int		each_elem(t_input *in, char *s, int i, int n);
void	parsing_elem(t_data *dt, char *s, int in);

//parsing_utils.c
int		check_quotes(t_input *input, char *s);
int		skip_spaces(char *s, int i);
void	space_counter(t_input *input, char *s);
int		skip_quotes(t_input *in, int i);
int		skip_n(t_input *in, int i);

//parsing_elem_utils.c
int		malloc_elem(t_input *in, char *s, int i, int n);
int		into_elem_quotes(t_input *in, char *s, int i, int n);
void	nb_cmd(t_data *dt, char *args, int i);

//quotes_mgmt.c
int		d_quotes_mgmt(t_input *input, char *s, int i, int n);
int		s_quotes_mgmt(t_input *input, char *s, int i, int n);
int		no_quote_mgmt(t_input *input, char *s, int i, int n);

//env_utils.c
char	**parse_env(char *s);
void	sort_env(t_data *dt, int in);
void	print_env(t_data *dt, char **elem);
void	the_sorter(t_data *dt, char *tempura, char *a, char *b);
// void	print_env(char **elem);
void	dup_array_to_env(t_data *dt, char **array);
void	freearray(char **m, int n);

//b_cd.c
int		b_cd(t_data *dt, int in);
int		where_in_env(t_data *dt, char *key, int len);
void	update_env(t_data *dt, char *dir);
int		print_cd(char *s, int n);
int		no_place_like_home(t_data *dt);

//b_export.c
// int		b_export(t_builtins *bs);
int		b_export(t_data *dt, int in);
void	add_key(t_data *dt, char *key, char *val);
char	*define_val(char *key, char *val);

//b_unset.c
int		b_unset(t_data *dt, int in);
void	remove_key(t_data *dt, char *key);

//b_echo.c
int		b_echo(t_data *dt, int in);
void	print_echo_n(t_input *in, int i);
void	print_echo_quotes(t_input *in, int i);
char	*entrequotes(char *s, int j);

//b_init.c
void	b_init(t_data *dt, char *envp[]);
void	malloc_checker(char *s);

//var.c
void	conv_var(t_data *dt, int in, int i);

//quotes_utils.c
char	*quotes_ignorer(char *s);
int		trimquotes(t_data *dt, char *s, int in, int i);


//redirections.c
// void	redir_input(t_builtins *bs);
// void	redir_output(t_builtins *bs);
// void	append_in(t_builtins *bs);
// void	heredoc(t_builtins *bs);

//execve.c
void	exec(t_data *dt, int in);

//signals.c
void	sig_int(int c);
void	sig_quit(int c);
void	ft_termios(void);

#endif
