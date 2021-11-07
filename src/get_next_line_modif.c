/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_modif.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:24:00 by rkhelif           #+#    #+#             */
/*   Updated: 2021/11/07 23:40:39 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_line_modif(int fd, char **line)
{
	char	buf[2];
	int		res;

	res = 0;
	if (line == NULL)
		return (-1);
	while (ft_strchr(*line, '\n') == NULL)
	{
		res = read(fd, buf, 1);
		if (res < 0)
			return (-1);
		buf[res] = '\0';
		if (buf[0] == '\n')
			return (res);
		*line = ft_strjoin(*line, buf);
	}
	return (res);
}
