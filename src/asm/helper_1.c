/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 16:12:01 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/01 16:12:13 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int 	start_condition(t_cont *cont)
{
	return (cont->type == COMMAND &&
			ft_strcmp(cont->content, ".name") &&
			ft_strcmp(cont->content, ".comment"));
}

/*
** Определяется формат, в котором записывать
** число в 16сс
*/

void	convert_to_hex_asm(int nbr, char *b_code, int pos, int size)
{
	int 	i;

	i = -8;
	while (size-- > 0)
		b_code[pos + size] = (unsigned char)(nbr >> (i += 8));
}

t_op	*get_operation(char *name)
{
	int 	i;

	i = -1;
	while (++i < 16)
		if (!ft_strcmp(g_op[i].name, name))
			return (&g_op[i]);
	return (NULL);
}

signed char		get_type(t_type type)
{
	if (type == REGISTER)
		return (T_REG);
	else if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else
		return (0);
}