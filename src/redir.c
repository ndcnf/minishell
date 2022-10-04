/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:08 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/04 16:22:53 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	exec_redir(t_data *dt)
{
	init_fd(dt);
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
