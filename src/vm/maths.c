/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:59:43 by asusan            #+#    #+#             */
/*   Updated: 2020/01/22 22:59:44 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int32_t	give_number(int fd, t_vm *vm)
{
	int32_t			res;
	int				i;
	unsigned char	buff[4];

	if ((read(fd, buff, 4)) < 1)
		error_1(ERROR_FILE, vm);
	res = 0;
	i = -1;
	while (++i != 4)
		res += (buff[3 - i] << ((i) * 8));
	return (res);
}

int		give_arg_val(const unsigned char *arr, int count_symb, int pos)
{
	int res;

	res = 0;
	if (count_symb == 4)
		res = (arr[increment_pos(pos, 0)] << 24) |
				(arr[increment_pos(pos, 1)] << 16) |
				(arr[increment_pos(pos, 2)] << 8) |
				arr[increment_pos(pos, 3)];
	else if (count_symb == 2)
		res = (arr[increment_pos(pos, 0)] << 8) |
				arr[increment_pos(pos, 1)];
	return (res);
}

void	write_to_map(t_vm *vm, int val, int pos, int size)
{
	if (size == 4)
	{
		vm->map[(increment_pos(pos, 0))] = (val >> 24);
		vm->map[(increment_pos(pos, 1))] = (val >> 16);
		vm->map[(increment_pos(pos, 2))] = (val >> 8);
		vm->map[(increment_pos(pos, 3))] = (val);
	}
	else if (size == 2)
	{
		vm->map[increment_pos(pos, 0)] = (val >> 8) & 15;
		vm->map[increment_pos(pos, 1)] = (val) & 15;
	}
}
