/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:55:55 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/22 22:55:57 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm	*initialization(int fd)
{
	t_asm	*assem;

	if (!(assem = (t_asm *)malloc(sizeof(t_asm))))
		error("Not allocated memory");
	assem->fd = fd;
	assem->row = 0;
	assem->name = NULL;
	assem->metka = NULL;
	assem->column = 0;
	assem->b_code = NULL;
	assem->comment = NULL;
	assem->content = NULL;
	assem->byte_pos = 0;
	assem->arg_byte = 0;
	assem->b_code_size = 0;
	return (assem);
}

t_cont	*init_content(t_asm *assem, t_type type)
{
	t_cont	*content;

	content = NULL;
	if (!(content = (t_cont *)malloc(sizeof(t_cont))))
		error("Not allocated memory");
	if (type == SEPARATOR || type == NEW_LINE)
		content->column = assem->column - 1;
	else
		content->column = assem->column;
	content->row = assem->row;
	content->content = NULL;
	content->type = type;
	content->next = NULL;
	return (content);
}