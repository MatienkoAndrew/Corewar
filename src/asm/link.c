/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:30:45 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/01 17:30:57 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_link	*init_link(t_asm *assem, t_cont *content, int size)
{
	t_link	*link;

	link = NULL;
	if (!(link = (t_link *)malloc(sizeof(t_link))))
		error("Not allocated memory");
	link->row = content->row;
	link->column = content->column;
	link->byte_pos = assem->byte_pos;
	link->arg_byte = assem->arg_byte;
	link->size = size;
	link->next = NULL;
	return (link);
}

void	new_link(t_link **link, t_link *new)
{
	t_link	*point;

	if (link)
	{
		if (*link)
		{
			point = *link;
			while (point->next)
				point = point->next;
			point->next = new;
		}
		else
			*link = new;
	}
}
