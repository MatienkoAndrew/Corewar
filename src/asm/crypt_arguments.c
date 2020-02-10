/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypt_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:07:19 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/10 18:07:30 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void			crypt_direct(t_asm *assem, t_cont *content, int size_arg)
{
	char		*name;
	int			start;
	int			size;
	t_metka		*metka;

	start = (content->type == DIRECT_LABEL) ? 2 : 1;
	size = (content->type == DIRECT_LABEL) ? size_arg : IND_SIZE;
	if (!(name = ft_strsub(content->content,
			start, ft_strlen(content->content) - start)))
		error("Not allocated memory");
	if ((metka = metka_exist(assem->metka, name)) == NULL)
	{
		metka = init_metka(name, -1);
		new_metka(&assem->metka, metka);
	}
	new_link(&metka->link, init_link(assem, content, size));
	ft_strdel(&name);
	assem->byte_pos += size;
}

void			crypt_register(t_asm *assem, t_cont *content)
{
	int		value;

	if (content->content[0] != 'r')
		error("Register must start with character \'r\'\n");
	value = ft_atoi(&content->content[1]);
	convert_to_hex_asm(value, assem->b_code, assem->byte_pos, 1);
	assem->byte_pos += 1;
}

void			crypt_number(t_asm *assem, t_cont *content, t_op *op)
{
	int		start;
	int		size;
	int		num;

	start = (content->type == DIRECT) ? 1 : 0;
	size = (content->type == DIRECT) ? op->t_dir_size : IND_SIZE;
	num = ft_atoi(&content->content[start]);
	convert_to_hex_asm(num, assem->b_code, assem->byte_pos, size);
	assem->byte_pos += size;
}

signed char		crypt_argument(t_asm *assem,
		t_cont **content, t_op *op, int count)
{
	signed char		type;

	type = get_type((*content)->type);
	if (!(op->args_types[count] & type))
		argument_error(op, *content, count + 1);
	if ((*content)->type == REGISTER)
		crypt_register(assem, *content);
	else if ((*content)->type == INDIRECT_LABEL \
			|| (*content)->type == DIRECT_LABEL)
		crypt_direct(assem, *content, op->t_dir_size);
	else if ((*content)->type == INDIRECT || (*content)->type == DIRECT)
		crypt_number(assem, *content, op);
	return (type);
}

signed char		crypt_arguments(t_asm *assem, t_cont **content, t_op *op)
{
	signed char		type;
	signed char		b_code_args;
	int				count;

	b_code_args = 0;
	count = -1;
	while (++count < op->args_num)
	{
		if ((*content)->type >= REGISTER && (*content)->type <= INDIRECT_LABEL)
		{
			type = crypt_argument(assem, content, op, count);
			b_code_args = renew_buffer(b_code_args, count, type);
			*content = (*content)->next;
		}
		if (count < op->args_num - 1)
		{
			if ((*content)->type != SEPARATOR)
				ft_error_asm(*content);
			*content = (*content)->next;
		}
	}
	return (b_code_args);
}
