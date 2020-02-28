/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:56:30 by asusan            #+#    #+#             */
/*   Updated: 2020/01/24 13:56:31 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		check_name(const char *arr)
{
	int i;

	i = -1;
	while (arr[++i] != '\0')
	{
		if (!ft_strcmp(arr + i, ".cor") && i > 0)
			return (1);
	}
	return (0);
}

int		check_on_digits(char *arr)
{
	int i;

	i = -1;
	while (arr[++i] != '\0')
		if (!ft_isdigit(arr[i]))
			return (0);
	return (1);
}

void	check_duplicate(t_vm *vm)
{
	int i;
	int j;

	i = -1;
	while (++i < vm->count_players)
	{
		j = i + 1;
		while (++j < vm->count_players)
		{
			if (vm->flags.n[j] == vm->flags.n[i] && vm->flags.n[i] != 0)
				error_1(ERROR_FLAGS, vm);
		}
	}
}

void	check(t_vm *vm)
{
	t_cursor *cursor;

	cursor = vm->cursor;
	while (cursor)
	{
		if ((int)vm->count_cycles - cursor->count_cycle_last_live >=
		vm->cycle_to_die || (vm->cycle_to_die <= 0 &&
		cursor->count_cycle_last_live < (int)vm->count_cycles))
		{
			check_to_die_cursor(vm, &vm->cursor, cursor->id);
			cursor = vm->cursor;
		}
		else
			cursor = cursor->next;
	}
	if (vm->count_live >= NBR_LIVE ||
	vm->count_cycles_to_max_checks >= MAX_CHECKS)
	{
		vm->count_cycles_to_max_checks = 0;
		vm->cycle_to_die -= CYCLE_DELTA;
	}
	else
		vm->count_cycles_to_max_checks++;
	vm->count_live = 0;
	vm->count_cycles_after_check = 0;
}
