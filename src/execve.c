/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchennaf <nchennaf@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:05:55 by mthiesso          #+#    #+#             */
/*   Updated: 2022/10/05 10:02:43 by nchennaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_boarders(t_data *dt, int in)
// {
// 	int			i;
// 	// int			status;
// 	int			ok;

// 	ok = 0;
// 	i = where_in_env(dt, "PATH", 4);
// 	if (i == NO_RESULT)
// 	{
// 		the_end(CMD_404, EXIT_FAILURE, 1);
// 		return ;
// 	}
// 	ok = exec_middle(dt, in, ok, i);
// 	if (ok == 0)
// 		the_end(CMD_404, EXIT_FAILURE, 1);
// 	// while (in < dt->n_cmd)
// 	// {
// 	// 	ft_printf("pid %d\n", dt->in[in].pid);
// 	// 	waitpid(dt->in[in++].pid, &status, 0);
// 	// }
// }

void	exec_boarders(t_data *dt, int in)
{
	int			i;
	int			ok;

	ok = 0;
	if (on_my_way(dt, ok, dt->in[in].elem->cont[0], in) != 1)
	{
		i = where_in_env(dt, "PATH", 4);
		if (i == NO_RESULT)
		{
			the_end(CMD_404, EXIT_FAILURE, 1);
			return ;
		}
		ok = exec_middle(dt, in, ok, i);
		if (ok == 0)
			the_end(CMD_404, EXIT_FAILURE, 1);
	}
	// while (in < dt->n_cmd)
	// {
	// 	waitpid(dt->in[in++].pid, &g_exit_stat, 0);
	// 	if (WIFSIGNALED(g_exit_stat))
	// 		g_exit_stat = ERR_SIGN + g_exit_stat;
	// 	if (WIFEXITED(g_exit_stat))
	// 		g_exit_stat = WEXITSTATUS(g_exit_stat);
	// }
}

int	exec_middle(t_data *dt, int in, int ok, int i)
{
	char		**tdpp;
	char		**tmp;
	char		*cmd_path;

	tmp = parse_env(dt->env[i]);
	tdpp = ft_split(tmp[1], ':');
	freearray(tmp, 2);
	i = 0;
	while (tdpp[i])
	{
		cmd_path = ft_strjoin_free(tdpp[i], "/");
		cmd_path = ft_strjoin_free(cmd_path, dt->in[in].elem->cont[0]);
		ok = on_my_way(dt, ok, cmd_path, in);
		i++;
		free(cmd_path);
	}
	free(tdpp);
	return (ok);
}

int	on_my_way(t_data *dt, int ok, char *cmd_path, int in)
{
	struct stat	buff;

	if (!stat(cmd_path, &buff))
	{
		ok = 1;
		dt->in[in].pid = fork();
		signal(SIGINT, sig_double);
		signal(SIGQUIT, sig_double);
		if (dt->in[in].pid == 0)
			execve(cmd_path, dt->in[in].elem->cont, dt->env);
	}
	return (ok);
}


// int	exec_middle(t_data *dt, int in, int ok, int i)
// {
// 	char		**tdpp;
// 	char		**tmp;
// 	char		*cmd_path;
// 	struct stat	buff;

// 	tmp = parse_env(dt->env[i]);
// 	tdpp = ft_split(tmp[1], ':');
// 	freearray(tmp, 2);
// 	i = 0;
// 	while (tdpp[i])
// 	{
// 		cmd_path = ft_strjoin_free(tdpp[i], "/");
// 		cmd_path = ft_strjoin_free(cmd_path, dt->in[in].elem->cont[0]);
// 		if (!stat(cmd_path, &buff))
// 		{
// 			ok = 1;
// 			dt->in[in].pid = fork();
// 			if (dt->in[in].pid == 0)
// 			{
// 				if (builtins_selector(dt, i) == NO_RESULT)
// 					execve(cmd_path, dt->in[in].elem->cont, dt->env);
// 			}
// 		}
// 		i++;
// 	}
// 	free(cmd_path);
// 	return (ok);
// }
