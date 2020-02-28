/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:49:50 by asusan            #+#    #+#             */
/*   Updated: 2020/02/14 16:49:52 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	die_my_head(t_cursor **cursor, int id)
{
	t_cursor *helper;

	helper = NULL;
	if ((*cursor)->id == id)
	{
		if ((*cursor)->next)
			helper = (*cursor)->next;
		free(*cursor);
		*cursor = NULL;
		if (helper)
			*cursor = helper;
	}
}

void	check_to_die_cursor(t_vm *vm, t_cursor **cursor, int id)
{
	t_cursor *temp;
	t_cursor *helper;

	temp = *cursor;
	while (temp)
	{
		helper = NULL;
		if (temp->next && temp->next->id == id)
		{
			if (temp->next->next)
				helper = temp->next->next;
			free(temp->next);
			temp->next = NULL;
			if (helper)
				temp->next = helper;
		}
		temp = temp->next;
	}
	die_my_head(&vm->cursor, id);
}
