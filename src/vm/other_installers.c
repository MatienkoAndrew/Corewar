/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_installers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:57:53 by asusan            #+#    #+#             */
/*   Updated: 2020/02/14 16:57:54 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	install_to_reg(int (*arr)[16], int id)
{
	int i;

	i = 0;
	(*arr)[0] = -id;
	while (++i != REG_NUMBER)
		(*arr)[i] = 0;
}

void	install_to_chrono(int **arr, int size, t_vm *vm)
{
	int i;
	int j;
	int val;

	val = 1;
	i = -1;
	if (vm->flags.d > 1 || vm->flags.dump > 1 ||
	vm->flags.count_n > vm->count_players)
		error_1(ERROR_FLAGS, vm);
	while (++i != size)
	{
		j = -1;
		while (++j != size)
		{
			if ((*arr)[j] == val)
				break ;
		}
		if (j == size)
			(*arr)[near_zero(*arr, size)] = val;
		val++;
	}
}

void	install_to_val(int **arr, int size, int val)
{
	int i;

	i = -1;
	while (++i != size)
		(*arr)[i] = val;
}

void	install_to_carry(t_vm *vm, int val)
{
	if (val == 0)
		vm->cursor_for_op->carry = 1;
	else
		vm->cursor_for_op->carry = 0;
}
