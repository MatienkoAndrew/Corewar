/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   installers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:51:42 by asusan            #+#    #+#             */
/*   Updated: 2020/01/22 22:51:43 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	base_install_player(t_player **player, t_vm *vm)
{
	if (!(*player = (t_player*)malloc(sizeof(t_player))))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	(*player)->name = NULL;
	(*player)->code = NULL;
	(*player)->code_size = 0;
	(*player)->comment = NULL;
	(*player)->id = 0;
	(*player)->next = NULL;
}

void	base_install_vm(t_vm *vm)
{
	vm->player = NULL;
	vm->cursor = NULL;
	vm->flags.n = NULL;
	vm->flags.aff = 0;
	vm->count_cursor = 1;
	vm->count_not_deleted = 1;
	vm->count_players = 0;
	bzero(vm->map, MEM_SIZE);
	vm->count_cycles = 0;
	vm->count_live = 0;
	vm->count_cycles_to_max_checks = 0;
	vm->count_cycles_after_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
}

void	install_pos_for_cursor(t_cursor *cursor, t_vm *vm)
{
	cursor->first_code = vm->map[(increment_pos(cursor->pos, 0))];
	if (vm->map[increment_pos(cursor->pos, 0)] >= 0x01
		&& vm->map[increment_pos(cursor->pos, 0)] <= 0x10)
		cursor->count_cycle_to_do = g_option
				[vm->map[increment_pos(cursor->pos, 0)] - 1].count_cycles;
	else
		cursor->pos = increment_pos(cursor->pos, 1);
}

int		base_install_to_parce_flags(t_vm *vm, int *count)
{
	if (!(vm->flags.n = (int*)malloc(sizeof(int) * vm->count_players)))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	vm->flags.d = 0;
	vm->flags.dump = 0;
	vm->flags.count_n = 0;
	install_to_val(&vm->flags.n, vm->count_players, 0);
	*count = 0;
	return (0);
}

void	base_install_to_cursor(t_cursor **cursor, t_player *player)
{
	(*cursor)->player = player;
	(*cursor)->id = player->id;
	(*cursor)->count_cycle_to_do = 0;
	(*cursor)->carry = 0;
	(*cursor)->count_cycle_last_live = 0;
	install_to_reg(&(*cursor)->regs, player->id);
}
