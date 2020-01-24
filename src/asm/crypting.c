/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 20:30:20 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/24 20:30:35 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int 	skip(t_cont *content)
{
	return (content->type == NEW_LINE || \
			content->type == COMMAND || \
			content->type == SEPARATOR || \
			content->type == STRING);
}

t_mark	*marker_exist(t_mark *marker, char *name)
{
	t_mark	*temp;

	temp = marker;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

t_mark	*init_marker(char *name, int point)
{
	t_mark	*marker;

	marker = NULL;
	if (!(marker = (t_mark *)malloc(sizeof(t_mark))))
		error("Not allocated memory");
	if (!(marker->name = ft_strdup(name)))
		error("Not allocated memory");
	marker->count = point;
	marker->link = NULL;
	marker->next = NULL;
	return (marker);
}

void 	new_marker(t_mark **marker, t_mark *new)
{
	t_mark	*point;

	if (marker)
	{
		if (*marker)
		{
			point = *marker;
			while (point->next)
				point = point->next;
			point->next = new;
		}
		else
			*marker = new;
	}
}

void	crypt_label(t_asm *assem, t_cont **content)
{
	char 	*name;
	t_mark	*marker;
	char 	*name_c;

	name_c = (*content)->content;
	if (!(name = ft_strsub(name_c, 0, ft_strlen(name_c) - 1)))
		error("Not allocated memory");
	marker = marker_exist(assem->marker, name);
	if (marker == NULL)
		new_marker(&assem->marker, init_marker(name, assem->point));
	ft_strdel(&name);
}

void	crypting(t_asm *assem)
{
	t_cont	*content;

	content = assem->content;
	while (content->type != END)
	{
		if (content->type == LABEL)
			crypt_label(assem, &content);
		if (skip(content))
			content = content->next;
	}
}