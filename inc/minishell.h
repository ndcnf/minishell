/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:25:30 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/04 12:00:38 by nchennaf         ###   ########.fr       */
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
# define ERR_REDIR 258

# define ERROR "Error\n"
# define OPT_IGN "Option(s) ignored\n"
# define ERR_ARG "Argument invalid in this scope\n"
# define ERR_NO_ARG "No argument(s) provided\n"
# define CMD_404 "command not found\n"
# define TM_ARG "too many arguments\n"
# define HOMELESS "HOME not set\n"
# define NOT_EVEN "Quotes are not closed\n"
# define NOT_NUM "numeric argument required\n"
# define ERR_MALL "malloc error\n"
# define ERR_CHEVRON "redirection error\n"

int		g_exit_stat;

// structure des listes chaînées afin de pouvoir stocker les arguments
//et de pouvoir les utiliser de manière optimisée
typedef struct s_elem
{
	char	**cont;
}	t_elem;

typedef struct s_redir
{
	char	*file;
	char	*chevron;
}	t_redir;

typedef struct s_input
{
	char	*cont;
	int		n_elem;
	t_elem	*elem;
	int		fd;
	t_redir	*red;
	int		n_redir;
	int		pos_red;
}	t_input;

typedef struct s_data
{
	char	**env;
	int		n_env;
	char	*path;
	int		n_cmd;
	t_input	*in;
	pid_t	pid;
}	t_data;

//prompt.c
void	prompt(char **envp);

//builtins.c
int		b_pwd(t_data *dt);
int		b_exit(t_data *dt, int in);
int		b_env(t_data *dt);

//cmd_selector.c
void	cmd_selector(t_data *dt, int i);
int		builtins_selector(t_data *dt, int i);

//parsing.c
int		parsing_init(char *args, t_data *dt);
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
int		nb_cmd(t_data *dt, char *args, int i);

//quotes_mgmt.c
int		d_quotes_mgmt(t_input *input, char *s, int i, int n);
int		s_quotes_mgmt(t_input *input, char *s, int i, int n);
int		no_quote_mgmt(t_input *input, char *s, int i, int n);

//env_utils.c
char	**parse_env(char *s);
void	sort_env(t_data *dt, int in);
void	print_env(t_data *dt, int in, char **elem);
void	the_sorter(t_data *dt, char *tempura, char *a, char *b);
void	dup_array_to_env(t_data *dt, char **array);

//b_cd.c
int		b_cd(t_data *dt, int in);
int		where_in_env(t_data *dt, char *key, int len);
void	update_env(t_data *dt, char *dir);
int		print_cd(char *s, int n);
int		no_place_like_home(t_data *dt);

//b_export.c
int		b_export(t_data *dt, int in);
void	add_key(t_data *dt, char *key, char *val);
char	*define_val(char *key, char *val);
void	update_arr(t_data *dt, char **new_array, int add_key, char *new_val);
void	update_key(t_data *dt, char *key, char *val, char **new_array);

//b_unset.c
int		b_unset(t_data *dt, int in);
void	remove_key(t_data *dt, char *key);

//b_echo.c
int		b_echo(t_data *dt, int in);
void	print_echo_n(t_input *in, int i);

//b_init.c
void	b_init(t_data *dt, char *envp[]);
void	malloc_checker(char *s);
void	freearray(char **m, int n);

//var.c
void	conv_var(t_data *dt, int in, int i);

//quotes_utils.c
int		trimquotes(t_data *dt, char *s, int in, int i);

//redirections.c
int		count_redir(t_data *dt, int in);
void	init_redir(t_data *dt, int in);
int		pop_redir(t_data *dt, int in, int i);
int		checker_redir(t_data *dt, int in, int i);
// void	redir_input(t_builtins *bs);
// void	redir_output(t_builtins *bs);
// void	append_in(t_builtins *bs);
// void	heredoc(t_builtins *bs);

//execve.c
void	exec(t_data *dt, int in);

//signals.c
void	sig_int(int c);
void	sig_double(int c);
void	ft_termios(void);

//error.c
int		the_end(char *msg, int status, int print);

//free.c
void	free_data(t_data *dt);
void	free_redir(t_data *dt, int i);

#endif
