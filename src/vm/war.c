/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:22:32 by asusan            #+#    #+#             */
/*   Updated: 2020/01/24 17:22:33 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	give_me_args(t_cursor *cursor, t_vm *vm, int i, int *counter)
{
	if (*counter == 3)
		error_1(ERROR_OPERATIONS, vm);
	if (cursor->type_args[i] == T_REG)
	{
		cursor->args_val[(*counter)++] = vm->map[increment_pos(cursor->pos, 0)];
		cursor->pos = increment_pos(cursor->pos, 1);
	}
	else if (cursor->type_args[i] == T_DIR)
	{
		if (g_option[cursor->first_code - 1].size_dir == 4)
			cursor->args_val[(*counter)++] = give_arg_val(vm->map,
					g_option[cursor->first_code - 1].size_dir, cursor->pos);
		else
			cursor->args_val[(*counter)++] =
			(int16_t)give_arg_val(vm->map,
					g_option[cursor->first_code - 1].size_dir, cursor->pos);
		cursor->pos = increment_pos(cursor->pos,
				g_option[cursor->first_code - 1].size_dir);
	}
	else if (cursor->type_args[i] == T_IND)
	{
		cursor->args_val[(*counter)++] =
		(int16_t)give_arg_val(vm->map, 2, cursor->pos);
		cursor->pos = increment_pos(cursor->pos, 2);
	}
}

void	do_something_my_cursor(t_vm *vm, t_cursor *cursor)
{
	int i;
	int counter;

	i = -1;
	counter = 0;
	ft_bzero(cursor->type_args, 3);
	check_args(vm, cursor);
	while (++i != g_option[cursor->first_code - 1].count_args)
		give_me_args(cursor, vm, i, &counter);
	if (!(check_on_valid_args(cursor)))
	{
		cursor->first_code = vm->map[cursor->pos];
		cursor->count_cycle_to_do = 0;
		return ;
	}
	vm->cursor_for_op = cursor;
	g_option[cursor->first_code - 1].func(vm);
	cursor->first_code = vm->map[cursor->pos];
}

void	act(t_vm *vm)
{
	t_cursor *cursor;

	cursor = vm->cursor;
	vm->count_cycles_after_check++;
	vm->count_cycles++;
	while (cursor)
	{
		if (cursor->count_cycle_to_do == 0)
			install_pos_for_cursor(cursor, vm);
		if (cursor->count_cycle_to_do > 0)
			cursor->count_cycle_to_do--;
		if (cursor->count_cycle_to_do == 0)
		{
			if (cursor->first_code >= 0x01 && cursor->first_code <= 0x10)
				do_something_my_cursor(vm, cursor);
		}
		cursor = cursor->next;
	}
}

void	war(t_vm *vm)
{
	int count;

	count = 0;
	while (vm->cursor && num_of_flag(vm, count) > count)
	{
		if (vm->count_cycles_after_check >=
		vm->cycle_to_die || vm->cycle_to_die <= 0)
			check(vm);
		act(vm);
		count++;
	}
	if (num_of_flag(vm, count) <= count)
		print_for_ddump(vm);
	else
		print_champ(vm);
}
