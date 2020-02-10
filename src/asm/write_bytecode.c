/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:48:33 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/02 13:48:46 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	write_string(char **bytecode, int point, char *name, int len)
{
	int		i;

	len = (len == 0) ? ft_strlen(name) : len;
	i = -1;
	while (++i < len)
		(*bytecode)[point++] = name[i];
}

void	write_bytecode(int fd, t_asm *assem)
{
	int		len_bytecode;
	int		point;
	char	*bytecode;

	len_bytecode = MAGIC_HEADER + CHAMPION_NAME +
			NULL_CW + CHAMPION_EXEC_CODE_SIZE +
			CHAMPION_COMMENT + NULL_CW + assem->byte_pos;
	if (!(bytecode = ft_strnew((size_t)len_bytecode)))
		error(MEMORY);
	point = 0;
	convert_to_hex_asm(COREWAR_EXEC_MAGIC, bytecode, point, 4);
	point += MAGIC_HEADER;
	write_string(&bytecode, point, assem->name, 0);
	point += CHAMPION_NAME + NULL_CW;
	convert_to_hex_asm(assem->byte_pos, bytecode, point, 4);
	point += CHAMPION_EXEC_CODE_SIZE;
	write_string(&bytecode, point, assem->comment, 0);
	point += CHAMPION_COMMENT + NULL_CW;
	write_string(&bytecode, point, assem->b_code, assem->byte_pos);
	write(fd, bytecode, len_bytecode);
	ft_strdel(&bytecode);
}
