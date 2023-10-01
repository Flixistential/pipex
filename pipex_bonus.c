/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:28:31 by fboivin           #+#    #+#             */
/*   Updated: 2023/10/01 18:46:26 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc < 5)
	{
		ft_putstr_fd("error\n", 2);
		return (-1);
	}
	pipe(fd);
	if (ft_fork(argv, envp) != 0)
	{
		ft_putstr_fd("error\n", 2);
		return (-1);
	}
}
