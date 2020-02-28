/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:27:57 by asusan            #+#    #+#             */
/*   Updated: 2020/02/06 17:27:58 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	args(t_vm *vm, t_cursor *cursor, int count)
{
	if (((vm->map[increment_pos(cursor->pos, 1)] >> count) & 3) == REG_CODE)
	{
		cursor->op_size++;
		return (T_REG);
	}
	else if (((vm->map[increment_pos(cursor->pos, 1)] >>
	count) & 3) == DIR_CODE)
	{
		cursor->op_size += g_option[cursor->first_code - 1].size_dir;
		return (T_DIR);
	}
	else if (((vm->map[increment_pos(cursor->pos, 1)] >>
	count) & 3) == IND_CODE)
	{
		cursor->op_size += 2;
		return (T_IND);
	}
	return (0);
}

void			check_args(t_vm *vm, t_cursor *cursor)
{
	cursor->op_size = 1;
	if (g_option[cursor->first_code - 1].code_type_args)
	{
		cursor->op_size++;
		cursor->type_args[0] = args(vm, cursor, 6);
		if (g_option[cursor->first_code - 1].count_args > 1)
			cursor->type_args[1] = args(vm, cursor, 4);
		if (g_option[cursor->first_code - 1].count_args > 2)
			cursor->type_args[2] = args(vm, cursor, 2);
		cursor->pos = increment_pos(cursor->pos, 2);
	}
	else
	{
		cursor->type_args[0] = g_option[cursor->first_code - 1].type_args[0];
		if (cursor->type_args[0] == 1)
			cursor->op_size++;
		else if (cursor->type_args[0] == 2)
			cursor->op_size += g_option[cursor->first_code - 1].size_dir;
		else if (cursor->type_args[0] == 3)
			cursor->op_size += 2;
		cursor->pos = increment_pos(cursor->pos, 1);
	}
}

int				check_on_valid_args(t_cursor *cursor)
{
	int i;

	i = -1;
	while (++i != g_option[cursor->first_code - 1].count_args)
	{
		if (cursor->type_args[i] == 0
		&& g_option[cursor->first_code - 1].type_args[i] != 0)
			return (0);
		if (cursor->type_args[i] == T_REG
		&& (cursor->args_val[i] < 1 || cursor->args_val[i] > 16))
			return (0);
		if (!(cursor->type_args[i] &
		g_option[cursor->first_code - 1].type_args[i]))
			return (0);
	}
	return (1);
}
