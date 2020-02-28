/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:09:45 by asusan            #+#    #+#             */
/*   Updated: 2020/02/14 17:09:46 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_sub(t_vm *vm)
{
	vm->cursor_for_op->regs[vm->cursor_for_op->args_val[2] - 1] =
			vm->cursor_for_op->regs[vm->cursor_for_op->args_val[0] - 1] -
			vm->cursor_for_op->regs[vm->cursor_for_op->args_val[1] - 1];
	install_to_carry(vm, vm->cursor_for_op->regs
	[vm->cursor_for_op->args_val[2] - 1]);
}

void	ft_and(t_vm *vm)
{
	int i;
	int *p;
	int helper;

	i = -1;
	p = (int*)malloc(sizeof(int) * 2);
	while (++i != 2)
	{
		if (vm->cursor_for_op->type_args[i] == T_REG)
			p[i] = vm->cursor_for_op->regs[vm->cursor_for_op->args_val[i] - 1];
		else if (vm->cursor_for_op->type_args[i] == T_DIR)
			p[i] = vm->cursor_for_op->args_val[i];
		else
		{
			helper = increment_pos(vm->cursor_for_op->pos -
					vm->cursor_for_op->op_size,
					vm->cursor_for_op->args_val[i] % IDX_MOD);
			p[i] = give_arg_val(vm->map, REG_SIZE, helper);
		}
	}
	helper = vm->cursor_for_op->args_val[2];
	install_to_carry(vm, (vm->cursor_for_op->regs[helper - 1] = (p[0] & p[1])));
	free(p);
}

void	ft_or(t_vm *vm)
{
	int i;
	int *p;
	int helper;

	i = -1;
	p = (int*)malloc(sizeof(int) * 2);
	while (++i != 2)
	{
		if (vm->cursor_for_op->type_args[i] == T_REG)
			p[i] = vm->cursor_for_op->regs[vm->cursor_for_op->args_val[i] - 1];
		else if (vm->cursor_for_op->type_args[i] == T_DIR)
			p[i] = vm->cursor_for_op->args_val[i];
		else
		{
			helper = increment_pos(vm->cursor_for_op->pos -
					vm->cursor_for_op->op_size,
					vm->cursor_for_op->args_val[i] % IDX_MOD);
			p[i] = give_arg_val(vm->map, REG_SIZE, helper);
		}
	}
	helper = vm->cursor_for_op->args_val[2];
	install_to_carry(vm, (vm->cursor_for_op->regs[helper - 1] = (p[0] | p[1])));
	free(p);
}

void	ft_xor(t_vm *vm)
{
	int i;
	int *p;
	int helper;

	i = -1;
	if (!(p = (int*)malloc(sizeof(int) * 2)))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	while (++i != 2)
	{
		if (vm->cursor_for_op->type_args[i] == T_REG)
			p[i] = vm->cursor_for_op->regs[vm->cursor_for_op->args_val[i] - 1];
		else if (vm->cursor_for_op->type_args[i] == T_DIR)
			p[i] = vm->cursor_for_op->args_val[i];
		else
		{
			helper = increment_pos(vm->cursor_for_op->pos -
					vm->cursor_for_op->op_size,
					vm->cursor_for_op->args_val[i] % IDX_MOD);
			p[i] = give_arg_val(vm->map, REG_SIZE, helper);
		}
	}
	helper = vm->cursor_for_op->args_val[2];
	install_to_carry(vm, (vm->cursor_for_op->regs[helper - 1] = (p[0] ^ p[1])));
	free(p);
}
