/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_selector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:54:27 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 20:37:21 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_selector(t_data *dt, int i)
{
	if (dt->n_cmd == 1)
	{
		dt->in[i].pid = NO_RESULT;
		if (builtins_selector(dt, i) == NO_RESULT)
			exec_boarders(dt, i);
	}
	else
		exec_boarders(dt, i);
}

void	bs_fd(t_data *dt, int i, t_fd *fdk)
{
	fdk->out = dup(STDOUT_FILENO);
	fdk->in = dup(STDIN_FILENO);
	if (dt->in[i].fd.out > 2)
	{
		dup2(dt->in[i].fd.out, STDOUT_FILENO);
		close(dt->in[i].fd.out);
	}
	if (dt->in[i].fd.in > 2)
	{
		dup2(dt->in[i].fd.in, STDIN_FILENO);
		close(dt->in[i].fd.in);
	}
}

void	reset_fd(t_fd *fdk)
{
	dup2(fdk->out, STDOUT_FILENO);
	dup2(fdk->in, STDIN_FILENO);
	close(fdk->out);
	close(fdk->in);
}

int	is_bs(t_data *dt, int i)
{
	int	bs;

	bs = 1;
	if (ft_strncmp(dt->in[i].elem->cont[0], "echo", 5) == 0)
		bs = 1;
	else if (ft_strncmp(dt->in[i].elem->cont[0], "pwd", 4) == 0)
		bs = 1;
	else if (ft_strncmp(dt->in[i].elem->cont[0], "cd", 3) == 0)
		bs = 1;
	else if (ft_strncmp(dt->in[i].elem->cont[0], "exit", 5) == 0)
		bs = 1;
	else if (ft_strncmp(dt->in[i].elem->cont[0], "env", 4) == 0)
		bs = 1;
	else if (ft_strncmp(dt->in[i].elem->cont[0], "export", 7) == 0)
		bs = 1;
	else if (ft_strncmp(dt->in[i].elem->cont[0], "unset", 6) == 0)
		bs = 1;
	else
		bs = 0;
	return (bs);
}

int	builtins_selector(t_data *dt, int i)
{
	t_fd	fd_keeper;

	ft_strtolower(dt->in[i].elem->cont[0]);
	if (is_bs(dt, i))
		bs_fd(dt, i, &fd_keeper);
	if (ft_strncmp(dt->in[i].elem->cont[0], "echo", 5) == 0)
		b_echo(dt, i);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "pwd", 4) == 0)
		b_pwd(dt);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "cd", 3) == 0)
		b_cd(dt, i);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "exit", 5) == 0)
		b_exit(dt, i);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "env", 4) == 0)
		b_env(dt);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "export", 7) == 0)
		b_export(dt, i);
	else if (ft_strncmp(dt->in[i].elem->cont[0], "unset", 6) == 0)
		b_unset(dt, i);
	else
		return (NO_RESULT);
	reset_fd(&fd_keeper);
	return (0);
}

char	*ft_strtolower(char *s)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
	return (s);
}
