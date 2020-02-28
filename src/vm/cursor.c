/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:50:14 by asusan            #+#    #+#             */
/*   Updated: 2020/01/23 19:50:15 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		install_code_to_map(t_vm *vm, t_player *player, int index)
{
	int i;

	i = -1;
	while (++i != player->code_size)
		vm->map[index + i] = player->code[i];
	return (i);
}

void	reverse(t_cursor **head)
{
	t_cursor *curr;
	t_cursor *next;
	t_cursor *prev;

	prev = NULL;
	curr = *head;
	if (*head == NULL)
		return ;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

void	initialize_arena(t_vm *vm)
{
	int			i;
	t_player	*player;
	t_cursor	*cursor;

	i = -1;
	cursor = vm->cursor;
	player = vm->player;
	while (++i != MEM_SIZE)
	{
		if (player && i == (player->id - 1) * (MEM_SIZE / vm->count_players))
		{
			cursor->pos = i;
			cursor->count_cycle_to_do = 0;
			i += install_code_to_map(vm, player, i);
			player = player->next;
			cursor = cursor->next;
		}
		else
			vm->map[i] = 0;
	}
	reverse(&vm->cursor);
}

void	install_head(t_vm *vm, t_player **player, t_cursor **cursor)
{
	if (vm->cursor == NULL)
	{
		if (!(vm->cursor = (t_cursor*)malloc(sizeof(t_cursor))))
			error_1(NOT_ALLOCATE_MEMORY, vm);
		base_install_to_cursor(&vm->cursor, *player);
		vm->cursor->id = vm->count_cursor;
		vm->count_cursor++;
		*cursor = vm->cursor;
		(*cursor)->next = NULL;
	}
	else
	{
		if (!((*cursor)->next = (t_cursor*)malloc(sizeof(t_cursor))))
			error_1(NOT_ALLOCATE_MEMORY, vm);
		*cursor = (*cursor)->next;
		(*cursor)->next = NULL;
		base_install_to_cursor(cursor, *player);
		(*cursor)->id = vm->count_cursor;
		vm->count_cursor++;
		vm->count_not_deleted++;
	}
}

void	create_cursor(t_vm *vm)
{
	t_player	*player;
	t_cursor	*cursor;
	int			i;

	i = -1;
	player = vm->player;
	while (++i != vm->count_players)
	{
		install_head(vm, &player, &cursor);
		player = player->next;
	}
	initialize_arena(vm);
}
