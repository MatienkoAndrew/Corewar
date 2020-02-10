/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:49:32 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/17 21:25:42 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static int	divide_str(char **str, char **row)
{
	char	*new;
	char	*div;

	div = ft_strchr_asm(*str, '\n');
	div++;
	if (!(*row = ft_strsub(*str, 0, div - *str)))
		return (-1);
	if (!ft_strlen(div))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	new = ft_strdup(div);
	free(*str);
	*str = new;
	return ((new) ? 1 : -1);
}

int			get_next_line(const int fd, char **row)
{
	static char		*str = NULL;
	char			buff[BUFF_SIZE + 1];
	size_t			size;
	char			*tmp;

	if (fd < 0 || !row || read(fd, buff, 0) < 0)
		return (-1);
	while (!ft_strchr_asm(str, '\n'))
	{
		if (!(size = read(fd, buff, BUFF_SIZE)))
		{
			if (!(*row = str))
				return (0);
			str = NULL;
			return (1);
		}
		buff[size] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (!str)
			return (-1);
	}
	return (divide_str(&str, row));
}
