/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cript_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:00:12 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/01 20:00:22 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	crypt_links(t_asm *assem)
{
	t_metka		*metka;
	t_link		*link;

	metka = assem->metka;
	while (metka)
	{
		if (metka->byte == -1)
			metka_error(metka);
		else
		{
			link = metka->link;
			while (link)
			{
				if (link->size == 2)
					convert_to_hex_asm((int16_t)(metka->byte - link->arg_byte),
							assem->b_code, link->byte_pos, link->size);
				else
					convert_to_hex_asm(metka->byte - link->arg_byte,
							assem->b_code, link->byte_pos, link->size);
				link = link->next;
			}
		}
		metka = metka->next;
	}
}
