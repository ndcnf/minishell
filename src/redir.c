/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:08 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/04 14:10:51 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_redir(t_data *dt, int in)
{
	dt->in[in].n_fd = dt->n_cmd - 1 + dt->in[in].n_redir;
	ft_printf("fd nombre: %d\n", dt->in[in].n_fd);
	ft_printf("cmd-1[%d] + nredir[%d]\n", (dt->n_cmd - 1), dt->in[in].n_redir);
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
