/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:14:04 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/22 23:14:14 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	add_content(t_asm **assem, t_cont *content)
{
	t_cont	*point;

	if (assem)
	{
		if ((*assem)->content)
		{
			point = (*assem)->content;
			while (point->next != NULL)
				point = point->next;
			if (point->type == NEW_LINE && content->type == NEW_LINE)
				ft_memdel((void **)&content);
			else
				point->next = content;
		}
		else
		{
			if (content->type == NEW_LINE)
				ft_memdel((void **)&content);
			else
				(*assem)->content = content;
		}
	}
}

void	parser(t_asm *assem, char **line)
{
	if (*(*line + assem->column) == SEPARATOR_CHAR && ++assem->column)
		add_content(&assem, init_content(assem, SEPARATOR));
	else if (*(*line + assem->column) == '\n' && ++assem->column)
		add_content(&assem, init_content(assem, NEW_LINE));
	else if (*(*line + assem->column) == '.')
		parser_symb(assem, *line,
				assem->column++, init_content(assem, COMMAND));
	else if (*(*line + assem->column) == '\"')
		parser_string(assem, line, assem->column, init_content(assem, STRING));
	else if (*(*line + assem->column) == DIRECT_CHAR && ++assem->column)
	{
		if (*(*line + assem->column) == LABEL_CHAR && ++assem->column)
			parser_symb(assem, *line, assem->column - 2,
					init_content(assem, DIRECT_LABEL));
		else
			parser_another(assem, *line,
					assem->column - 1, init_content(assem, DIRECT));
	}
	else if (*(*line + assem->column) == LABEL_CHAR)
		parser_symb(assem, *line, assem->column++,
				init_content(assem, INDIRECT_LABEL));
	else
		parser_another(assem, *line, assem->column,
				init_content(assem, INDIRECT));
}

void	validation(t_asm *assem)
{
	int		size;
	char	*line;

	size = 0;
	line = NULL;
	while ((size = get_next_line(assem->fd, &line)) > 0)
	{
		assem->row += 1;
		while (line[assem->column] != '\0')
		{
			while (is_help(line[assem->column]))
				assem->column += 1;
			if (line[assem->column] == '#' || line[assem->column] == ';')
				while (line[assem->column] && line[assem->column] != '\n')
					assem->column += 1;
			if (line[assem->column] != '\0')
				parser(assem, &line);
		}
		assem->column = 0;
		ft_strdel(&line);
	}
	if (size == -1)
		error("Bad file");
	assem->row += 1;
	add_content(&assem, init_content(assem, END));
}
