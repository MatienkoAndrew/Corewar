/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 13:54:53 by asusan            #+#    #+#             */
/*   Updated: 2020/01/24 13:54:54 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int	count_players(int ac, char **av, t_vm *vm)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (++i != ac)
	{
		if (check_name(av[i]))
			count++;
	}
	vm->count_players = count;
	check_flags(ac, av, vm);
	return (count);
}

int	near_zero(const int *arr, int size)
{
	int i;

	i = -1;
	while (++i != size)
	{
		if (arr[i] == 0)
			return (i);
	}
	return (-1);
}
