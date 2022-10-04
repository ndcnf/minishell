/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:08 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/04 19:26:11 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	mgmnt_fd(t_data *dt)
{
	int	i;
	int	j;

	i = 0;
	while (i < dt->n_cmd)
	{
		j = 0;
		while (j < dt->in[i].n_redir)
		{
			open_fd(dt, i, j);
			j++;
		}
		i++;
	}
}

void	open_fd(t_data *dt, int i, int j)
{
	if (!ft_strncmp(dt->in[i].red[j].chevron, ">", 2))
	{
		redir_output(dt, i, j);
	}
	else if (!ft_strncmp(dt->in[i].red[j].chevron, "<", 2))
	{
		redir_input(dt, i, j);
	}
	else if (!ft_strncmp(dt->in[i].red[j].chevron, ">>", 3))
	{
		append_in(dt, i, j);
	}
	else if (!ft_strncmp(dt->in[i].red[j].chevron, "<<", 3))
	{
		heredoc(dt, i, j);

	}
}

void	init_fd(t_data *dt)
{
	int	i;
	int	fd[2];

	dt->in[0].fd.in = STDIN_FILENO;
	dt->in[dt->n_cmd - 1].fd.out = STDOUT_FILENO;
	i = 0;
	while (i < dt->n_cmd - 1)
	{
		if (pipe(fd) == NO_RESULT)
			exit (the_end(ERR_PIPE, EXIT_FAILURE, 1));
		dt->in[i].fd.out = fd[1];
		dt->in[i + 1].fd.in = fd[0];
		i++;
	}
	mgmnt_fd(dt);
}

void	exec_redir(t_data *dt)
{
	init_fd(dt);
}

// '<'
void	redir_input(t_data *dt, int i, int j)
{
	int	fd;

	ft_printf("file[%s]\n", dt->in[i].red[j].file);
	fd = open(dt->in[i].red[j].file, O_RDONLY);
	if (fd == NO_RESULT)
	{
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	}
	else
	{
		if (dt->in[i].fd.in > 2)
			close(dt->in[i].fd.in);
		dt->in[i].fd.in = fd;
		char c;
		while (read(fd, &c, 1))
			ft_putchar_fd(c, 1);
	}
}

// '>'
void	redir_output(t_data *dt, int i, int j)
{
	int	fd;

	ft_printf("file[%s]\n", dt->in[i].red[j].file);
	fd = open(dt->in[i].red[j].file, O_CREAT | O_WRONLY, 0644);
	if (fd == NO_RESULT)
	{
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	}
	else
	{
		if (dt->in[i].fd.out > 2)
			close(dt->in[i].fd.out);
		dt->in[i].fd.out = fd;
	}

	// dup2(fd, STDOUT_FILENO); // sera a faire en dernier dans le programme (niveau cmd_selector par exemple))
	// close(fd); // idem
}

// '>>'
void	append_in(t_data *dt, int i, int j)
{
	int	fd;

	ft_printf("file[%s]\n", dt->in[i].red[j].file);
	fd = open(dt->in[i].red[j].file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == NO_RESULT)
	{
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	}
	else
	{
		if (dt->in[i].fd.out > 2)
			close(dt->in[i].fd.out);
		dt->in[i].fd.out = fd;
	}
}

// '<<'
void	heredoc(t_data *dt, int i, int j)
{
	int		fd[2];
	char	*keyword;
	char	*prompt;

	if (pipe(fd) == NO_RESULT)
	{
		the_end(ERR_PIPE, EXIT_FAILURE, 1);
	}
	keyword = dt->in[i].red[j].file;
	prompt = NULL;
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
			break ;
		if (ft_strncmp(prompt, keyword, ft_strlen(keyword)))
			ft_putendl_fd(prompt, fd[1]);
		else
			break;
		free(prompt);
	}
	free(prompt);
	close(fd[1]);
	ft_printf("file[%s]\n", dt->in[i].red[j].file);

	if (dt->in[i].fd.in > 2)
		close(dt->in[i].fd.in);
	dt->in[i].fd.in = fd[0];
}
