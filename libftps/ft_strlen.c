/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:39 by fboivin           #+#    #+#             */
/*   Updated: 2023/08/28 18:55:32 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftps.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}
