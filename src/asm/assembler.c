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

void	assembler(char *file_name)
{
	int		fd;
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
