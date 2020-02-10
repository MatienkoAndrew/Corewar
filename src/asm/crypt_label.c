/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypt_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:39:55 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/01 13:40:07 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_metka		*metka_exist(t_metka *metka, char *name)
{
	t_metka		*temp;

	temp = metka;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_metka		*init_metka(char *name, int byte)
{
	t_metka		*metka;

	metka = NULL;
	if (!(metka = (t_metka *)malloc(sizeof(t_metka))))
		error("Not allocated memory");
	if (!(metka->name = ft_strdup(name)))
		error("Not allocated memory");
	metka->byte = byte;
	metka->link = NULL;
	metka->next = NULL;
	return (metka);
}

void		new_metka(t_metka **metka, t_metka *new)
{
	t_metka		*point;

	if (metka)
	{
		if (*metka)
		{
			point = *metka;
			while (point->next)
				point = point->next;
			point->next = new;
		}
		else
			*metka = new;
	}
}

void		crypt_label(t_asm *assem, t_cont **content)
{
	char	*name;
	t_metka	*metka;
	char	*name_c;

	name_c = (*content)->content;
	if (!(name = ft_strsub(name_c, 0, ft_strlen(name_c) - 1)))
		error("Not allocated memory");
	metka = metka_exist(assem->metka, name);
	if (metka == NULL)
		new_metka(&assem->metka, init_metka(name, assem->byte_pos));
	if (metka && metka->byte == -1)
		metka->byte = assem->byte_pos;
	ft_strdel(&name);
	*content = (*content)->next;
}
