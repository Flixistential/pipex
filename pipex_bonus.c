/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:28:31 by fboivin           #+#    #+#             */
/*   Updated: 2023/10/04 21:10:07 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	fprintf(stderr, "pipe : %d,cmd i: %d, cmd count : %d\n", data->pipe_i, data->cmd_i, data->count_cmd);
		if (data->cmd_i == (data->count_cmd + 1))
		{
			data->fdout = open(av[data->count_cmd + 2], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->fdout < 0)
			{
				ft_putstr_fd("pipex: permission denied: ", 2);
				ft_putendl_fd(av[data->count_cmd + 2], 2);
				exit(0);
			}
			fprintf(stderr, "last :%d\n", data->cmd_i);
			dup2 (data->fdout, STDOUT_FILENO);
			fprintf(stderr,"LAST PIPE :%d\n", data->pipe_i);
			close (data->pipe[data->pipe_i][1]);
			close(data->fdout);
			close(data->fdin);
		}
		else
		{
			fprintf(stderr,"midDDDD :%d\n", data->pipe_i);
			dup2(data->pipe[data->pipe_i + 1][1], STDOUT_FILENO);
			close(data->pipe[data->pipe_i][1]);
			close(data->pipe[data->pipe_i + 1][0]);
		}
		command (av[data->cmd_i], env);
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
		data->fdin = open (av[1], O_RDONLY, 0777);
		if (data->fdin < 0)
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putendl_fd(av[1], 2);
			//free;
			exit(0);
		}
		fprintf(stderr,"first :%d\n", data->cmd_i);
		dup2(data->fdin, STDIN_FILENO);
		dup2((data->pipe[data->pipe_i][1]), STDOUT_FILENO);
		close(data->fdin);
		close (data->pipe[data->pipe_i][0]);
		command (av[2], env);
	}
}

int	make_pid(int cmd, pid_t **pid) 
{
	*pid = (pid_t *)malloc(cmd * sizeof(pid_t));
	if (!pid)
		return (0);
	return (1);
}

void	make_cmd(t_pipex *data, char **av, char **env)
{
	int i;

	i = 0;
	data->pid_i = 0;
	data->pipe_i = 0;
	data->cmd_i = 2;
	cmd_first(data, av, env);
	while(data->cmd_i <= data->count_cmd)
	{
		data->cmd_i++;
		fprintf(stderr, "cmd i before : %d\n", data->cmd_i);
		cmd_middle(data, av , env);
		data->pipe_i++;
	}
	/*close(data->fdout);
	close(data->fdin);
	while (i <= data->pipe_i)
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i++;
	}*/
}

int **make_pipes(int cmd)
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int i;
	int status;

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
	make_cmd(&data, argv, envp);
	ft_printf("data pid :%d\n", data.pid_i);
	while(i < data.pid_i)
	{
	
		waitpid(data.childs[i], &status, 0);
		ft_printf("Hello\n");
		i++;
	}
}
