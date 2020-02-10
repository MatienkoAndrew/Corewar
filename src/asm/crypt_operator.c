/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypt_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:43:13 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/01 13:43:26 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

signed char		get_type_arg(signed char type)
{
	if (type == T_REG)
		return (REG_CODE);
	else if (type == T_DIR)
		return (DIR_CODE);
	else
		return (IND_CODE);
}

signed char		renew_buffer(signed char b_code_args,
		int count_arg, signed char type)
{
	type = get_type_arg(type);
	type <<= 2 * (3 - count_arg);
	b_code_args |= type;
	return (b_code_args);
}

void			crypt_operator(t_asm *assem, t_cont **content)
{
	t_op			*op;
	signed char		b_code;

	if ((op = get_operation((*content)->content)))
	{
		assem->b_code[assem->byte_pos++] = op->code;
		*content = (*content)->next;
		if (op->args_types_code)
			assem->byte_pos += 1;
		b_code = crypt_arguments(assem, content, op);
		if (op->args_types_code)
			assem->b_code[assem->arg_byte + 1] = b_code;
	}
	else
		operator_error(*content);
}
