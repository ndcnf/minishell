/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiesso <mthiesso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:08 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 21:41:01 by mthiesso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_redir(t_data *dt)
{
	init_fd(dt);
	mgmnt_fd(dt);
}

// '<'
void	redir_input(t_data *dt, int i, int j)
{
	int	fd;

	fd = open(dt->in[i].red[j].file, O_RDONLY);
	if (fd == NO_RESULT)
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	else
	{
		if (dt->in[i].fd.in > 2)
			close(dt->in[i].fd.in);
		dt->in[i].fd.in = fd;
	}
}

// '>'
void	redir_output(t_data *dt, int i, int j)
{
	int	fd;

	fd = open(dt->in[i].red[j].file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == NO_RESULT)
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	else
	{
		if (dt->in[i].fd.out > 2)
			close(dt->in[i].fd.out);
		dt->in[i].fd.out = fd;
	}
}

// '>>'
void	append_in(t_data *dt, int i, int j)
{
	int	fd;

	fd = open(dt->in[i].red[j].file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == NO_RESULT)
		the_end(ERR_FILE, EXIT_FAILURE, 1);
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
		the_end(ERR_PIPE, EXIT_FAILURE, 1);
	keyword = dt->in[i].red[j].file;
	prompt = NULL;
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
			break ;
		if (ft_strncmp(prompt, keyword, (ft_strlen(keyword) + 1)))
			ft_putendl_fd(prompt, fd[1]);
		else
			break ;
		free(prompt);
	}
	free(prompt);
	close(fd[1]);
	if (dt->in[i].fd.in > 2)
		close(dt->in[i].fd.in);
	dt->in[i].fd.in = fd[0];
}
