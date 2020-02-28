/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:02:28 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 23:02:30 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	byte_code_aff(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x10 - 1].name);
	parser->pos++;
	ft_aff(parser, state);
}

void	byte_code_lfork(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x0f - 1].name);
	parser->pos++;
	ft_fork(parser, state);
}

void	byte_code_lldi(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x0e - 1].name);
	parser->pos++;
	ft_ldi(parser, state);
}
