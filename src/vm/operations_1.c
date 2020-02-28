/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:06:27 by asusan            #+#    #+#             */
/*   Updated: 2020/02/14 17:06:29 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_live(t_vm *vm)
{
	if (vm->cursor_for_op->player->id == (-1) * vm->cursor_for_op->args_val[0])
		vm->cursor_for_op->player->cycle_live = vm->count_cycles;
	vm->cursor_for_op->count_cycle_last_live = vm->count_cycles;
	if ((-1) * vm->cursor_for_op->args_val[0] <= vm->count_players &&
	vm->cursor_for_op->args_val[0] < 0)
		vm->last_player_who_live = (-1) * vm->cursor_for_op->args_val[0];
	vm->count_live++;
}

void	ft_ld(t_vm *vm)
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
		vm->cursor_for_op->args_val[0] %= IDX_MOD;
		helper = give_arg_val(vm->map, REG_SIZE,
		increment_pos(vm->cursor_for_op->pos -
		vm->cursor_for_op->op_size, vm->cursor_for_op->args_val[0]));
		install_to_carry(vm, (vm->cursor_for_op->regs
		[vm->cursor_for_op->args_val[1] - 1] = helper));
	}
}

void	ft_st(t_vm *vm)
{
	int helper;

	if (vm->cursor_for_op->type_args[1] == T_REG)
	{
		vm->cursor_for_op->regs[vm->cursor_for_op->args_val[1] - 1] =
				vm->cursor_for_op->regs[vm->cursor_for_op->args_val[0] - 1];
	}
	else
	{
		vm->cursor_for_op->args_val[1] %= IDX_MOD;
		helper = vm->cursor_for_op->regs[vm->cursor_for_op->args_val[0] - 1];
		write_to_map(vm, helper, increment_pos(vm->cursor_for_op->pos -
		vm->cursor_for_op->op_size, vm->cursor_for_op->args_val[1]), DIR_SIZE);
	}
}

void	ft_add(t_vm *vm)
{
	vm->cursor_for_op->regs[vm->cursor_for_op->args_val[2] - 1] =
	vm->cursor_for_op->regs[vm->cursor_for_op->args_val[0] - 1] +
	vm->cursor_for_op->regs[vm->cursor_for_op->args_val[1] - 1];
	install_to_carry(vm, vm->cursor_for_op->regs
	[vm->cursor_for_op->args_val[2] - 1]);
}
