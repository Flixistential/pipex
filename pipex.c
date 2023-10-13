/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:05:50 by fboivin           #+#    #+#             */
/*   Updated: 2023/09/10 23:05:50 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_closeall(int *pipe_fd, int fd)
{
	if (fd > 0)
		close (fd);
	close (pipe_fd[1]);
	close (pipe_fd[0]);
}

void	wait_close(int *fd, pid_t child1, pid_t child2)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}

void	cmd_1(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open (av[1], O_RDONLY, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(av[1], 2);
		ft_closeall(pipe_fd, fd);
		exit(0);
	}
	dup2 (fd, STDIN_FILENO);
	dup2 (pipe_fd[1], STDOUT_FILENO);
	ft_closeall(pipe_fd, fd);
	command (av[2], env);
}

void	cmd_2(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(av[4], 2);
		ft_closeall(pipe_fd, fd);
		exit(0);
	}
	dup2 (fd, STDOUT_FILENO);
	dup2 (pipe_fd[0], STDIN_FILENO);
	ft_closeall(pipe_fd, fd);
	command (av[3], env);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;

	if (ac != 5)
	{
		ft_putstr_fd("Wrong no of arguments\n", 2);
		return (-1);
	}
	if (pipe(fd) == -1)
		exit (-1);
	child1 = fork();
	if (child1 < 0)
		exit (-1);
	if (!child1)
		cmd_1(av, fd, envp);
	child2 = fork();
	if (child1 < 0)
		exit (-1);
	if (!child2)
		cmd_2(av, fd, envp);
	wait_close(fd, child1, child2);
}
