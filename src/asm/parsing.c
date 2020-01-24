/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 20:55:13 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/23 20:55:30 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	parser_symb(t_asm *assem, char *line, int col, t_cont *cont)
{
	int 	i;

	cont->column = col;
	i = assem->column;
	while (line[assem->column] && ft_strchr(LABEL_CHARS, line[assem->column]))
		assem->column += 1;
	if (assem->column - i > 0 && line[assem->column] == LABEL_CHAR)
	{
		assem->column += 1;
		cont->content = ft_strsub(line, i, assem->column);
		cont->type = LABEL;
		add_content(&assem, cont);
	}
	else if (assem->column - i > 0 && is_conditions(line[assem->column]))
	{
		cont->content = ft_strsub(line, col, assem->column - col);
		if (cont->type == INDIRECT)
			cont->type = (is_registr(cont->content)) ? REGISTER : OPERATOR;
		add_content(&assem, cont);
	}
	else
		ft_printf("Lexical error at [%d,%d]", assem->row, assem->column);
}

void	parser_string(t_asm *assem, char **line, int col, t_cont *cont)
{
	char 	*end;
	int		size;
	char 	*str;

	assem->column = col;
	size = 1;
	while ((end = ft_strchr(&((*line)[col + 1]), '\"')) == NULL)
		if ((size = get_next_line(assem->fd, &str)) > 0)
			*line = ft_strjoin_asm(line, &str);
	new_info(assem, *line);
	if (size == -1)
		error("Bad file");
	else if (size == 0)
		ft_printf("Lexical error at [%d:%d]", assem->row, assem->column);
	if (!(cont->content = ft_strsub(*line, col, end - &((*line)[col]) + 1)))
		error("Not allocated memory");
	new_line(line, end, assem->column);
	assem->column += 1;
	add_content(&assem, cont);
}

void	parser_another(t_asm *assem, char *line, int start, t_cont *cont)
{
	int 	i;

	cont->column = start;
	line[assem->column] == '-' ? assem->column++ : 0;
	i = assem->column;
	while (ft_isdigit(line[assem->column]))
		assem->column += 1;
	if (assem->column - i > 0 && (cont->type == DIRECT || is_conditions(line[assem->column])))
	{
		if (!(cont->content = ft_strsub(line, start, assem->column - start)))
			error("Not allocated memory");
		add_content(&assem, cont);
	}
	else if (cont->type != DIRECT)
	{
		assem->column = start;
		parser_symb(assem, line, start, cont);
	}
	else
		ft_printf("Lexical error [%d:%d]", assem->row, assem->column);
}
