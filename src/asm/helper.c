/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:10:10 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/23 21:10:22 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int 	is_help(char c)
{
	return (c == ' ' ||
			c == '\t' ||
			c == '\r');
}

int 	is_conditions(char c)
{
	if (c == ' ' || c == '\n' || c == '\0' || c == ',')
		return (1);
	return (0);
}

int 	is_registr(const char *str)
{
	int 	i;
	int 	num;

	i = 0;
	if (ft_strlen(str) >= 2 && ft_strlen(str) <= 3 && str[0] == 'r')
	{
		i += 1;
		while (ft_isdigit(str[i]))
			i++;
		num = ft_atoi(str + 1);
		return (str[i] == '\0' && num > 0);
	}
	return (0);
}

void	new_info(t_asm *assem, char *line)
{
	int 	i;

	i = ++assem->column;
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '\n')
		{
			assem->row += 1;
			assem->column = 0;
		}
		else
			assem->column += 1;
		i++;
	}
}

void	new_line(char **line, char *end, int col)
{
	char 	*new;

	new = NULL;
	if (ft_strcmp(end - col, *line))
	{
		if (!(new = ft_strdup(end)))
			error("Not allocated memory");
		ft_strdel(line);
		*line = new;
	}
}
