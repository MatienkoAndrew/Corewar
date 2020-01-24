/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:10:12 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/22 22:10:13 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	freeer(t_asm *assem)
{
	t_cont	*temp;

	ft_strdel(&assem->name);
	ft_strdel(&assem->comment);
	temp = assem->content;
	while (assem->content)
	{
		ft_strdel(&assem->content->content);
		temp = assem->content->next;
		free(assem->content);
		assem->content = NULL;
		assem->content = temp;
	}
	free(assem);
}

void	assembler(char *file_name)
{
	int 	fd;
	t_asm	*assem;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error("Bad file\n");
	assem = initialization(fd);
	validation(assem);
	get_name_comment(assem);
	crypting(assem);
	freeer(assem);
}
