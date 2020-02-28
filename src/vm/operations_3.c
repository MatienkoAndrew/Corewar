/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:20:05 by asusan            #+#    #+#             */
/*   Updated: 2020/02/14 17:20:07 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_zjmp(t_vm *vm)
{
	if (vm->cursor_for_op->carry == 0)
		return ;
	vm->cursor_for_op->pos = increment_pos(vm->cursor_for_op->pos -
			vm->cursor_for_op->op_size,
			vm->cursor_for_op->args_val[0] % IDX_MOD);
}

void	ft_ldi(t_vm *vm)
{
	int i;
	int *p;
	int helper;

	i = -1;
	if (!(p = (int*)malloc(sizeof(int) * 2)))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	while (++i != 2)
		if (vm->cursor_for_op->type_args[i] == T_REG)
			p[i] = vm->cursor_for_op->regs[vm->cursor_for_op->args_val[i] - 1];
		else if (vm->cursor_for_op->type_args[i] == T_DIR)
			p[i] = vm->cursor_for_op->args_val[i];
		else if (i == 0)
		{
			helper = increment_pos(vm->cursor_for_op->pos -
					vm->cursor_for_op->op_size,
					vm->cursor_for_op->args_val[i] % IDX_MOD);
			p[i] = give_arg_val(vm->map, REG_SIZE, helper);
		}
	helper = increment_pos(vm->cursor_for_op->pos -
			vm->cursor_for_op->op_size, (p[0] + p[1]) % IDX_MOD);
	vm->cursor_for_op->regs[vm->cursor_for_op->args_val
	[2] - 1] = give_arg_val(vm->map, REG_SIZE, helper);
	free(p);
}

void	ft_sti(t_vm *vm)
{
	int i;
	int *p;
	int helper;

	i = 0;
	if (!(p = (int*)malloc(sizeof(int) * 3)))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	while (++i != 3)
		if (vm->cursor_for_op->type_args[i] == T_REG)
			p[i] = vm->cursor_for_op->regs[vm->cursor_for_op->args_val[i] - 1];
		else if (vm->cursor_for_op->type_args[i] == T_DIR)
			p[i] = vm->cursor_for_op->args_val[i];
		else if (i == 1)
		{
			helper = increment_pos(vm->cursor_for_op->pos -
					vm->cursor_for_op->op_size,
					vm->cursor_for_op->args_val[i] % IDX_MOD);
			p[i] = give_arg_val(vm->map, REG_SIZE, helper);
		}
	helper = increment_pos(vm->cursor_for_op->pos -
			vm->cursor_for_op->op_size, (p[1] + p[2]) % IDX_MOD);
	write_to_map(vm, vm->cursor_for_op->regs
	[vm->cursor_for_op->args_val[0] - 1], helper, REG_SIZE);
	free(p);
}

void	ft_fork(t_vm *vm)
{
	t_cursor	*cursor;
	int			i;

	i = -1;
	if (!(cursor = (t_cursor*)malloc(sizeof(t_cursor))))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	while (++i != REG_NUMBER)
		cursor->regs[i] = vm->cursor_for_op->regs[i];
	cursor->carry = vm->cursor_for_op->carry;
	cursor->count_cycle_last_live = vm->cursor_for_op->count_cycle_last_live;
	cursor->pos = increment_pos((vm->cursor_for_op->pos -
			vm->cursor_for_op->op_size) + vm->
					cursor_for_op->args_val[0] % IDX_MOD, 0);
	cursor->count_cycle_to_do = 0;
	cursor->player = vm->cursor_for_op->player;
	cursor->id = vm->count_cursor;
	vm->count_cursor++;
	vm->count_not_deleted++;
	cursor->next = vm->cursor;
	vm->cursor = cursor;
}
