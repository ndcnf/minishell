/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:03:11 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/04 11:55:49 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_redir(t_data *dt, int in)
{
	int	cnt;
	int	j;

	cnt = 0;
	j = 0;
	while (j < dt->in->n_elem)
	{
		if (ft_strncmp(dt->in[in].elem->cont[j], ">", 2) == 0)
			cnt++;
		else if (ft_strncmp(dt->in[in].elem->cont[j], "<", 2) == 0)
			cnt++;
		else if (ft_strncmp(dt->in[in].elem->cont[j], ">>", 3) == 0)
			cnt++;
		else if (ft_strncmp(dt->in[in].elem->cont[j], "<<", 3) == 0)
			cnt++;
		j++;
	}
	return (cnt);
}

void	init_redir(t_data *dt, int in)
{
	dt->in[in].n_redir = count_redir(dt, in);
	dt->in[in].pos_red = 0;
	if (dt->in[in].n_redir > 0)
	{
		dt->in[in].red = ft_calloc(sizeof(t_redir), dt->in[in].n_redir);
		malloc_checker((char *)dt->in[in].red);
	}
	dt->in[in].n_redir = 0;
}

void	shift_elem(t_data *dt, int in, int i)
{
	int	j;

	j = i;
	while (j < dt->in[in].n_elem)
	{
		dt->in[in].elem->cont[j] = dt->in[in].elem->cont[j + 1];
		j++;
	}
	dt->in[in].n_elem--;
}

int	pop_redir(t_data *dt, int in, int i)
{
	int	j;

	j = dt->in[in].pos_red;
	dt->in[in].red[j].chevron = dt->in[in].elem->cont[i];
	shift_elem(dt, in, i);
	if (i < dt->in[in].n_elem)
	{
		dt->in[in].red[j].file = dt->in[in].elem->cont[i];
		shift_elem(dt, in, i);
		dt->in[in].n_redir++;
	}
	else
	{
		dt->in[in].n_redir++;
		dt->in[in].pos_red = NO_RESULT;
		return (the_end(ERR_CHEVRON, ERR_REDIR, 1));
	}
	dt->in[in].pos_red++;
	return (dt->in[in].pos_red);
}

int	checker_redir(t_data *dt, int in, int i)
{
	int	err;

	err = 0;
	if (ft_strncmp(dt->in[in].elem->cont[i], ">", 2) == 0)
	{
		err = pop_redir(dt, in, i);
	}
	else if (ft_strncmp(dt->in[in].elem->cont[i], "<", 2) == 0)
	{
		err = pop_redir(dt, in, i);
	}
	else if (ft_strncmp(dt->in[in].elem->cont[i], ">>", 3) == 0)
	{
		err = pop_redir(dt, in, i);
	}
	else if (ft_strncmp(dt->in[in].elem->cont[i], "<<", 3) == 0)
	{
		err = pop_redir(dt, in, i);
	}
	return (err);
}

// '<'
// void	redir_input(t_builtins *bs)
// {

// }

// '>'
// void	redir_output(t_builtins *bs)
// {
// 	int	fd;

// 	fd = open(bs->file, O_RDONLY | O_WRONLY);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	// printf("Je suis ici\n");
// }

// '<<'
// void	append_in(t_builtins *bs)
// {

// }

// '>>'
// void	heredoc(t_builtins *bs)
// {

// }
