/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:40:40 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 23:48:06 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	byte_code_ld(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x02 - 1].name);
	parser->pos++;
	ft_ld(parser, state);
}

void	byte_code_live(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x01 - 1].name);
	parser->pos++;
	ft_live(parser, state);
}

void	byte_code_sti(t_parser *parser, t_state **state)
{
	(*state)->name = ft_strdup(g_op[0x0b - 1].name);
	parser->pos++;
	ft_sti(parser, state);
}

void	byte_code_help(t_parser *parser, t_state **state)
{
	if (parser->code[parser->pos] == 0x08)
		byte_code_xor(parser, state);
	else if (parser->code[parser->pos] == 0x07)
		byte_code_or(parser, state);
	else if (parser->code[parser->pos] == 0x0a)
		byte_code_ldi(parser, state);
	else if (parser->code[parser->pos] == 0x0c)
		byte_code_fork(parser, state);
	else if (parser->code[parser->pos] == 0x0d)
		byte_code_lld(parser, state);
	else if (parser->code[parser->pos] == 0x0e)
		byte_code_lldi(parser, state);
	else if (parser->code[parser->pos] == 0x0f)
		byte_code_lfork(parser, state);
	else if (parser->code[parser->pos] == 0x10)
		byte_code_aff(parser, state);
}

void	bytecode_to_code(t_parser *parser, t_state **state)
{
	while (parser->pos < parser->code_size - 1)
	{
		(*state)->next = (t_state*)malloc(sizeof(t_state));
		(*state)->next->name = NULL;
		(*state)->next->next = NULL;
		if (parser->code[parser->pos] == 0x0b)
			byte_code_sti(parser, state);
		else if (parser->code[parser->pos] == 0x01)
			byte_code_live(parser, state);
		else if (parser->code[parser->pos] == 0x02)
			byte_code_ld(parser, state);
		else if (parser->code[parser->pos] == 0x09)
			byte_code_zjmp(parser, state);
		else if (parser->code[parser->pos] == 0x03)
			byte_code_st(parser, state);
		else if (parser->code[parser->pos] == 0x04)
			byte_code_add(parser, state);
		else if (parser->code[parser->pos] == 0x05)
			byte_code_sub(parser, state);
		else if (parser->code[parser->pos] == 0x06)
			byte_code_and(parser, state);
		else
			byte_code_help(parser, state);
	}
}
