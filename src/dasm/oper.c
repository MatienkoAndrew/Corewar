/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:30:18 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 23:30:19 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	ft_aff(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = ft_args(parser, 6);
	if ((*state)->argv[0] != REG_CODE)
		ft_exit("ERROR OPERATION CODE\n");
	parser->pos++;
	(*state)->f_argv[0] = parser->code[parser->pos];
	parser->pos++;
	(*state) = (*state)->next;
}

void	ft_ldi_help(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = ft_args(parser, 6);
	(*state)->argv[1] = ft_args(parser, 4);
	(*state)->argv[2] = ft_args(parser, 2);
	if ((*state)->argv[1] == IND_CODE || (*state)->argv[2] != REG_CODE)
		ft_exit("ERROR OPERATION CODE\n");
	parser->pos++;
	if ((*state)->argv[0] == DIR_CODE || (*state)->argv[1] == IND_CODE)
	{
		(*state)->f_argv[0] = (int16_t)(parser->code[parser->pos] << 8 |\
				parser->code[parser->pos + 1]);
		parser->pos += 2;
	}
	else
	{
		(*state)->f_argv[0] = parser->code[parser->pos];
		parser->pos++;
	}
}

void	ft_ldi(t_parser *parser, t_state **state)
{
	ft_ldi_help(parser, state);
	if ((*state)->argv[1] == DIR_CODE)
	{
		(*state)->f_argv[1] = (int16_t)(parser->code[parser->pos] << 8 |\
				parser->code[parser->pos + 1]);
		parser->pos += 2;
	}
	else
	{
		(*state)->f_argv[1] = (int8_t)parser->code[parser->pos];
		parser->pos++;
	}
	(*state)->f_argv[2] = parser->code[parser->pos];
	parser->pos++;
	(*state) = (*state)->next;
}

void	ft_fork(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = DIR_CODE;
	(*state)->f_argv[0] = (int16_t)(parser->code[parser->pos] << 8 |\
			parser->code[parser->pos + 1]);
	parser->pos += 2;
	(*state) = (*state)->next;
}

void	ft_lld(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = ft_args(parser, 6);
	(*state)->argv[1] = ft_args(parser, 4);
	if ((*state)->argv[0] == REG_CODE || (*state)->argv[1] != REG_CODE)
		ft_exit("ERROR OPERATION CODE\n");
	parser->pos++;
	if ((*state)->argv[0] == DIR_CODE)
	{
		(*state)->f_argv[0] = (parser->code[parser->pos] << 24 |\
		parser->code[parser->pos + 1] << 16 |\
		parser->code[parser->pos + 2] << 8 | parser->code[parser->pos + 3]);
		parser->pos = parser->pos + 4;
	}
	else
	{
		(*state)->f_argv[0] = (int16_t)(parser->code[parser->pos] << 8\
		| parser->code[parser->pos + 1]);
		parser->pos += 2;
	}
	(*state)->f_argv[1] = parser->code[parser->pos];
	parser->pos++;
	(*state) = (*state)->next;
}
