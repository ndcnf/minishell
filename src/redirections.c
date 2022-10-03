/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:03:11 by nchennaf          #+#    #+#             */
/*   Updated: 2022/10/03 14:24:03 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		count_redir(t_data *dt, int in)
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
	if (dt->in[in].n_redir > 0)
	{
		dt->in[in].red = malloc(sizeof(t_redir) * dt->in[in].n_redir);
		malloc_checker((char *)dt->in[in].red);
	}
	// pop_redir(dt, in);
}

void	pop_redir(t_data *dt, int in, int i)
{
	static int	s_i = 0;

	dt->in[in].red[s_i].chevron = ft_strdup(dt->in[in].elem->cont[i]);
	if (i + 1 <= dt->in[in].n_elem)
	{
		dt->in[in].red[s_i].file = ft_strdup(dt->in[in].elem->cont[i + 1]);
	}
	else
		the_end(ERR_CHEVRON, -10, 1); // ----------------------------------------- Erreur de retour a changer
	// ft_printf("redir [%s] : [%s]\n", dt->in[in].red[s_i].chevron, dt->in[in].red[s_i].file);
	s_i++;
	// free(dt->in[in].elem->cont[i]);
	// free(dt->in[in].elem->cont[i + 1]);
}

void	checker_redir(t_data *dt, int in, int i)
{
	if (ft_strncmp(dt->in[in].elem->cont[i], ">", 2) == 0)
	{
		// ft_printf("Cas 1 >\n");
		pop_redir(dt, in, i);
	}
	else if (ft_strncmp(dt->in[in].elem->cont[i], "<", 2) == 0)
	{
		// ft_printf("Cas 2 <\n");
		pop_redir(dt, in, i);
	}
	else if (ft_strncmp(dt->in[in].elem->cont[i], ">>", 3) == 0)
	{
		// ft_printf("Cas 3 >>\n");
		pop_redir(dt, in, i);
	}
	else if (ft_strncmp(dt->in[in].elem->cont[i], "<<", 3) == 0)
	{
		// ft_printf("Cas 4 <<\n");
		pop_redir(dt, in, i);
	}
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
