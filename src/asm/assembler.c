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
	t_metka	*temp_m;
	t_link 	*temp_l;

	ft_strdel(&assem->name);
	ft_strdel(&assem->comment);
	ft_strdel(&assem->b_code);
	temp = assem->content;
	while (assem->content)
	{
		ft_strdel(&assem->content->content);
		temp = assem->content->next;
		free(assem->content);
		assem->content = NULL;
		assem->content = temp;
	}
	while (assem->metka)
	{
		while (assem->metka->link)
		{
			temp_l = assem->metka->link->next;
			free(assem->metka->link);
			assem->metka->link = NULL;
			assem->metka->link = temp_l;
		}
		ft_strdel(&assem->metka->name);
		temp_m = assem->metka->next;
		free(assem->metka);
		assem->metka = NULL;
		assem->metka = temp_m;
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
	crypt_links(assem);
	new_filename(&file_name, &fd);
	write_bytecode(fd, assem);
	ft_printf("Writing output program to %s\n", file_name);
	ft_strdel(&file_name);
	freeer(assem);
}
