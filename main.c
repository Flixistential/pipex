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

char	*truepath(char *cmd, char **env)
{
	int		i;
	char	**s_path;
	char	**s_cmd;
	char	*path;

	i = -1;
	s_path = ft_split(pathfinder(env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (s_path[++i])
	{
		path = ft_strjoinslash(s_path[i], s_cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free(s_cmd);
			ft_free(s_path);
			return (path);
		}
		free(path);
	}
	ft_free(s_path);
	ft_free(s_cmd);
	return (NULL);
}

void	command(char *cmd, char **env)
{
	char	*path;
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	path = truepath(cmd, env);
	if (!path)
	{
		ft_putstr_fd("command not found :", 2);
		ft_putendl_fd(cmd, 2);
		ft_free(s_cmd);
		exit(2);
	}
	execve(path, s_cmd, env);
}

void	child(char **av, int *pipe_fd, char **env)
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

void	parent(char **av, int *pipe_fd, char **env)
{
	int	fd;
	int	status;

	waitpid(-1, &status, 0);
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
	pid_t	family;

	if (ac != 5)
	{
		ft_putstr_fd("Wrong no of arguments\n", 2);
		return (-1);
	}
	if (pipe(fd) == -1)
		exit (-1);
	family = fork();
	if (family < 0)
		exit (-1);
	if (!family)
		child(av, fd, envp);
	parent(av, fd, envp);
}

/* 
    pour trouver le PATH dans l'environnement :
    incrementer jusqu'a PATH=
    split sur les :
    split sur la cmd sur les ' ' pour isoler la commande
    ajouter /cmd a tout les path possible 
    vérifier si on peut y acceder avec access donc si le path est valide

*/

