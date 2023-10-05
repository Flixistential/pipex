/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 04:24:00 by fboivin           #+#    #+#             */
/*   Updated: 2023/09/12 04:24:00 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libftps/libftps.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h> 
# include <stdio.h>

char	*ft_strjoinslash(char const *s1, char const *s2);
char	*pathfinder(char **env);
void	command(char *cmd, char **env);
char	*truepath(char *cmd, char **env);

typedef struct	s_pipex
{
	int		fdout;
	int		fdin;
	int		pid_i;
	int		pipe_i;
	int		cmd_i;
	int		count_cmd;
	int		**pipe;
	pid_t	*childs;
}			t_pipex;

# endif