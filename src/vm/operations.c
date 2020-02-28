/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:25:56 by asusan            #+#    #+#             */
/*   Updated: 2020/02/01 13:25:57 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_lfork(t_vm *vm)
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
	cursor->pos = increment_pos(vm->cursor_for_op->pos -
			vm->cursor_for_op->op_size, vm->cursor_for_op->args_val[0]);
	cursor->count_cycle_to_do = 0;
	cursor->player = vm->cursor_for_op->player;
	cursor->id = vm->count_cursor;
	vm->count_cursor++;
	cursor->next = vm->cursor;
	vm->count_not_deleted++;
	vm->cursor = cursor;
}

void	ft_lld(t_vm *vm)
{
	int helper;

	if (vm->cursor_for_op->type_args[0] == T_DIR)
	{
		if ((vm->cursor_for_op->regs[vm->cursor_for_op->args_val[1] - 1] =
				vm->cursor_for_op->args_val[0]) == 0)
			vm->cursor_for_op->carry = 1;
		else
			vm->cursor_for_op->carry = 0;
	}
	else
	{
		helper = give_arg_val(vm->map, REG_SIZE,
				increment_pos(vm->cursor_for_op->pos -
				vm->cursor_for_op->op_size, vm->cursor_for_op->args_val[0]));
		install_to_carry(vm, (vm->cursor_for_op->regs
		[helper] = vm->cursor_for_op->args_val[0]));
	}
}

void	ft_lldi(t_vm *vm)
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
			vm->cursor_for_op->op_size, (p[0] + p[1]));
	install_to_carry(vm, (vm->cursor_for_op->regs[vm->
	cursor_for_op->args_val[2] - 1] = give_arg_val(vm->map, REG_SIZE, helper)));
	free(p);
}

void	ft_aff(t_vm *vm)
{
	char c;

	c = vm->cursor_for_op->regs[vm->cursor_for_op->args_val[0] - 1];
	if (vm->flags.aff == 1)
		ft_printf("\nAff: %c", c);
}
