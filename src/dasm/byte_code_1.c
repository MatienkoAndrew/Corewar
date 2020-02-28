/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:56:32 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 22:56:34 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	byte_code_and(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x06 - 1].name);
	parser->pos++;
	ft_and(parser, state);
}

void	byte_code_sub(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x05 - 1].name);
	parser->pos++;
	ft_sub(parser, state);
}

void	byte_code_add(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x04 - 1].name);
	parser->pos++;
	ft_add(parser, state);
}

void	byte_code_st(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x03 - 1].name);
	parser->pos++;
	ft_st(parser, state);
}

void	byte_code_zjmp(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x09 - 1].name);
	parser->pos++;
	ft_zjmp(parser, state);
}
