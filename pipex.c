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
#include <stdio.h>
#include <unistd.h>


void	cmd_1(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open (av[1], O_RDONLY, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(av[1], 2);
		exit(0);
	}
	dup2 (fd, STDIN_FILENO);
	dup2 (pipe_fd[1], STDOUT_FILENO);
	close (pipe_fd[0]);
	command (av[2], env);
}

void	cmd_2(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(av[4], 2);
		exit(0);
	}
	dup2 (fd, STDOUT_FILENO);
	dup2 (pipe_fd[0], STDIN_FILENO);
	close (pipe_fd[1]);
	command (av[3], env);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	int		status;
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
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

/* 
    pour trouver le PATH dans l'environnement :
    incrementer jusqu'a PATH=
    split sur les :
    split sur la cmd sur les ' ' pour isoler la commande
    ajouter /cmd a tout les path possible 
    vérifier si on peut y acceder avec access donc si le path est valide
*/

