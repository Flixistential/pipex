/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:29:10 by fboivin           #+#    #+#             */
/*   Updated: 2023/04/13 16:13:15 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

int	ft_make_nl(char **next_line, char *stash)
{
	char	*temp;
	char	*end;
	size_t	len;

	len = ft_strlen(*next_line);
	if (ft_strlen(stash) <= 0)
		return (0);
	end = ft_strchr(stash, '\n');
	if (!end)
		end = ft_strchr(stash, '\0');
	else
		end++;
	temp = *next_line;
	*next_line = ft_calloc(1, len + (end - stash) + 1);
	if (!next_line)
		return (0);
	ft_strlcpy(*next_line, temp, len + 1);
	ft_strlcat(*next_line, stash, len + (end - stash) + 1);
	ft_strlcpy(stash, end, (ft_strlen(end) + 1));
	free(temp);
	if (ft_strchr(*next_line, '\n'))
		return (1);
	else
		return (0);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*next_line;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = NULL;
	len = 1;
	while (len > 0 && !ft_make_nl(&next_line, stash))
	{
		len = read(fd, stash, BUFFER_SIZE);
		if (len < 0)
		{
			if (next_line)
				free (next_line);
			return (NULL);
		}
		stash[len] = '\0';
	}
	return (next_line);
}
