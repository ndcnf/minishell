/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_again.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:25:05 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/05 21:35:43 by nchennaf         ###   ########.fr       */
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
		redir_output(dt, i, j);
	else if (!ft_strncmp(dt->in[i].red[j].chevron, "<", 2))
		redir_input(dt, i, j);
	else if (!ft_strncmp(dt->in[i].red[j].chevron, ">>", 3))
		append_in(dt, i, j);
	else if (!ft_strncmp(dt->in[i].red[j].chevron, "<<", 3))
		heredoc(dt, i, j);
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
}

void	reset_fd(t_fd *fdk)
{
	dup2(fdk->out, STDOUT_FILENO);
	dup2(fdk->in, STDIN_FILENO);
	close(fdk->out);
	close(fdk->in);
}
