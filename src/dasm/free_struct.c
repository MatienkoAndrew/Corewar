/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:18:03 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 23:18:05 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	ft_free_char(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	free_state(t_state **list)
{
	t_state	*current;
	t_state	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		free(delete->name);
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void	ft_free(t_parser **parser, t_state **state)
{
	ft_strdel(&((*parser)->name));
	ft_strdel(&((*parser)->comment));
	ft_memdel((void **)&((*parser)->code));
	free_state(&(*state));
	ft_memdel((void **)parser);
	ft_memdel((void **)state);
}
