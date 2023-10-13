/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:06:19 by fboivin           #+#    #+#             */
/*   Updated: 2023/10/13 13:49:04 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	make_pid(int cmd, pid_t **pid)
{
	*pid = (pid_t *)malloc(cmd * sizeof(pid_t));
	if (!pid)
		return (0);
	return (1);
}

void	make_cmd(t_pipex *data, char **av, char **env)
{
	data->pid_i = 0;
	data->pipe_i = 0;
	data->cmd_i = 2;
	cmd_first(data, av, env);
	while (data->cmd_i <= data->count_cmd)
	{
		data->cmd_i++;
		cmd_middle(data, av, env);
		data->pipe_i++;
	}
}

int	**make_pipes(int cmd)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_calloc((cmd -1), sizeof(int *));
	if (!pipes)
		return (0);
	while (i < (cmd - 1))
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
			return (0);
		i++;
	}
	return (pipes);
}

void	ft_closepipe(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (data->count_cmd -1))
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i++;
	}
	if (data->fdin > 0)
		close(data->fdin);
	if (data->fdout > 0)
		close(data->fdout);
}

void	open_file(t_pipex *data, char **av)
{
	data->fdout = open(av[data->count_cmd + 2] \
	, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fdout < 0)
	{
		ft_putstr_fd("pipex: wrong outfile: ", 2);
		ft_putendl_fd(av[data->count_cmd + 2], 2);
	}
	data->fdin = open (av[1], O_RDONLY, 0777);
	if (data->fdin < 0)
	{
		ft_putstr_fd("pipex: wrong infile: ", 2);
		ft_putendl_fd(av[1], 2);
	}
}
