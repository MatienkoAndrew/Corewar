/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_fu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:30:17 by asusan            #+#    #+#             */
/*   Updated: 2020/02/06 17:30:18 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		num_of_flag(t_vm *vm, int count)
{
	if (vm->flags.dump)
		return (vm->flags.dump_val);
	else if (vm->flags.d)
		return (vm->flags.dump_val);
	return (count + 1);
}

int		increment_pos(int val, int count)
{
	int temp;

	if (val + count < MEM_SIZE && val + count >= 0)
		return (val + count);
	else if (val + count < 0)
	{
		temp = (val + count) % MEM_SIZE;
		return (MEM_SIZE + temp);
	}
	return ((val + count) % MEM_SIZE);
}

int		check_overval(char *arr, t_vm *vm)
{
	int		val;
	char	*temp;

	val = ft_atoi(arr);
	temp = ft_itoa(val);
	if (ft_strcmp(temp, arr))
	{
		free(temp);
		error_1(ERROR_INPUT, vm);
	}
	free(temp);
	return (val);
}

void	create_player_list(t_vm *vm, t_player **player)
{
	t_player *temp;

	temp = vm->player;
	while (temp->next)
		temp = temp->next;
	temp->next = *player;
}

void	all_val_down(int **arr, int size)
{
	int i;

	i = -1;
	while (++i != size)
		(*arr)[i] -= 1;
}
