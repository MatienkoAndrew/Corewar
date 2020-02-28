/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:59:01 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 22:59:03 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	byte_code_or(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x07 - 1].name);
	parser->pos++;
	ft_and(parser, state);
}

void	byte_code_lld(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x0d - 1].name);
	parser->pos++;
	ft_lld(parser, state);
}

void	byte_code_fork(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x0c - 1].name);
	parser->pos++;
	ft_fork(parser, state);
}

void	byte_code_ldi(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x0a - 1].name);
	parser->pos++;
	ft_ldi(parser, state);
}

void	byte_code_xor(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x08 - 1].name);
	parser->pos++;
	ft_and(parser, state);
}
