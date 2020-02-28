/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:53:23 by asusan            #+#    #+#             */
/*   Updated: 2020/01/24 16:53:25 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	print_players(t_vm *vm)
{
	t_player	*temp;
	int			i;

	i = 1;
	temp = vm->player;
	ft_printf("Introducing contestants...");
	while (temp)
	{
		temp->id += i;
		ft_printf("\n* Player %d, weighing %d bytes, \"%s\" (\"%s\") !",
				temp->id, temp->code_size, temp->name, temp->comment);
		temp = temp->next;
		i++;
	}
}

void	helper_for_print(t_vm *vm, int val, int index)
{
	if (index % val == 0)
		ft_printf("\n0x%.4x : ", index);
	ft_printf("%.2x ", vm->map[index]);
}

void	print_for_ddump(t_vm *vm)
{
	int i;

	i = -1;
	while (++i != MEM_SIZE)
	{
		if (vm->flags.dump)
			helper_for_print(vm, 32, i);
		else if (vm->flags.d)
			helper_for_print(vm, 64, i);
	}
	write(1, "\n", 1);
}

void	print_champ(t_vm *vm)
{
	t_player *player;

	player = vm->player;
	while (player)
	{
		if (vm->last_player_who_live == player->id)
		{
			ft_printf("\nContestant %d, \"%s\", has won !\n",
					player->id, player->name);
			return ;
		}
		player = player->next;
	}
}
