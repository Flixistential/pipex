/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:28:31 by fboivin           #+#    #+#             */
/*   Updated: 2023/10/17 17:35:12 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pp(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (data->count_cmd - 1))
	{
		free(data->pipe[i]);
		i++;
	}
	free(data->pipe);
	data->pipe = NULL;
	free(data->childs);
	data->childs = NULL;
}

void	cmd_middle(t_pipex *data, char	**av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		data->childs[data->pid_i] = pid;
		data->pid_i++;
	}
	else
	{
		dup2(data->pipe[data->pipe_i][0], STDIN_FILENO);
		if (data->cmd_i == (data->count_cmd + 1))
		{
			if (data->fdout < 0)
				ft_close(data);
			dup2 (data->fdout, STDOUT_FILENO);
		}
		else
			dup2(data->pipe[data->pipe_i + 1][1], STDOUT_FILENO);
		ft_closepipe(data);
		bonus_command (data, av[data->cmd_i], env);
	}
}

void	cmd_first(t_pipex *data, char **av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		data->childs[data->pid_i] = pid;
		data->pid_i++;
	}
	else
	{
		if (data->fdin < 0)
		{
			ft_closepipe(data);
			free_pp(data);
			exit(0);
		}
		dup2(data->fdin, STDIN_FILENO);
		dup2((data->pipe[data->pipe_i][1]), STDOUT_FILENO);
		ft_closepipe(data);
		bonus_command (data, av[2], env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		i;

	i = 0;
	ft_bzero(&data, sizeof(t_pipex));
	if (argc < 5)
		return (-1);
	data.count_cmd = (argc - 3);
	data.pipe = make_pipes(data.count_cmd);
	if (!data.pipe)
		return (-1);
	if (!make_pid(data.count_cmd, &data.childs))
		return (-1);
	open_file(&data, argv);
	make_cmd(&data, argv, envp);
	ft_closepipe(&data);
	while (i < data.pid_i)
	{
		waitpid(data.childs[i], NULL, 0);
		i++;
	}
	free_pp(&data);
}
