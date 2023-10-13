/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:46:54 by fboivin           #+#    #+#             */
/*   Updated: 2023/10/12 16:59:44 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	bonus_command(t_pipex *data, char *cmd, char **env)
{
	char	*path;
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	path = truepath(cmd, env);
	if (!path)
	{
		free_pp(data);
		ft_putstr_fd("Command not found :", 2);
		ft_putendl_fd(cmd, 2);
		ft_free(s_cmd);
		exit(2);
	}
	execve(path, s_cmd, env);
}

void	ft_close(t_pipex *data)
{
	ft_closepipe(data);
	free_pp(data);
	exit(0);
}
