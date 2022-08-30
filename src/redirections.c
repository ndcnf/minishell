/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:03:11 by nchennaf          #+#    #+#             */
/*   Updated: 2022/08/30 13:02:10 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// '<'
void	redir_input(t_builtins *bs)
{

}

// '>'
void	redir_output(t_builtins *bs)
{
	int	fd;

	fd = open(bs->file, O_RDONLY | O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	// printf("Je suis ici\n");






}

// '<<'
void	append_in(t_builtins *bs)
{

}

// '>>'
void	heredoc(t_builtins *bs)
{

}
