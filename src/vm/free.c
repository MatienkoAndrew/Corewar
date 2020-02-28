/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:44:17 by asusan            #+#    #+#             */
/*   Updated: 2020/01/23 21:44:19 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	free_players(t_vm *vm)
{
	t_player *temp;
	t_player *helper;

	temp = vm->player;
	while (temp)
	{
		helper = temp->next;
		free(temp->comment);
		free(temp->code);
		free(temp->name);
		free(temp);
		temp = helper;
	}
}

void	free_cursors(t_vm *vm)
{
	t_cursor *temp;
	t_cursor *helper;

	temp = vm->cursor;
	while (temp)
	{
		helper = temp->next;
		free(temp);
		temp = helper;
	}
}

void	free_all(t_vm *vm)
{
	free_players(vm);
	free_cursors(vm);
	free(vm->flags.n);
}
