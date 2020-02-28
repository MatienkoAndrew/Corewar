/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:31:34 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 23:31:35 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	ft_add(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = ft_args(parser, 6);
	(*state)->argv[1] = ft_args(parser, 4);
	(*state)->argv[2] = ft_args(parser, 2);
	if ((*state)->argv[0] != REG_CODE || (*state)->argv[1] != REG_CODE ||\
	(*state)->argv[2] != REG_CODE)
		ft_exit("ERROR OPERATION CODE\n");
	parser->pos++;
	(*state)->f_argv[0] = parser->code[parser->pos];
	parser->pos++;
	(*state)->f_argv[1] = parser->code[parser->pos];
	parser->pos++;
	(*state)->f_argv[2] = parser->code[parser->pos];
	parser->pos++;
	(*state) = (*state)->next;
}

void	ft_st(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = ft_args(parser, 6);
	(*state)->argv[1] = ft_args(parser, 4);
	if ((*state)->argv[0] != REG_CODE || (*state)->argv[1] == DIR_CODE)
		ft_exit("ERROR OPERATION CODE\n");
	parser->pos++;
	(*state)->f_argv[0] = parser->code[parser->pos];
	parser->pos++;
	if ((*state)->argv[1] == DIR_CODE)
	{
		(*state)->f_argv[1] = (parser->code[parser->pos] << 24 |\
		parser->code[parser->pos + 1] << 16 |\
		parser->code[parser->pos + 2] << 8 |\
		parser->code[parser->pos + 3]);
		parser->pos = parser->pos + 4;
	}
	else
		(*state)->f_argv[1] = (int16_t)(parser->code[parser->pos] << 8 |\
		parser->code[parser->pos + 1]);
	parser->pos += 2;
	(*state) = (*state)->next;
}

void	ft_sub(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = ft_args(parser, 6);
	(*state)->argv[1] = ft_args(parser, 4);
	(*state)->argv[2] = ft_args(parser, 2);
	if ((*state)->argv[0] != REG_CODE || (*state)->argv[1] != REG_CODE ||\
	(*state)->argv[2] != REG_CODE)
		ft_exit("ERROR OPERATION CODE\n");
	parser->pos++;
	(*state)->f_argv[0] = parser->code[parser->pos];
	parser->pos++;
	(*state)->f_argv[1] = parser->code[parser->pos];
	parser->pos++;
	(*state)->f_argv[2] = parser->code[parser->pos];
	parser->pos++;
	(*state) = (*state)->next;
}

void	ft_and_help(t_parser *parser, t_state **state, int i)
{
	if ((*state)->argv[i] == DIR_CODE)
	{
		(*state)->f_argv[i] = (parser->code[parser->pos] << 24 |\
		parser->code[parser->pos + 1] << 16 |\
		parser->code[parser->pos + 2] << 8 |\
		parser->code[parser->pos + 3]);
		parser->pos = parser->pos + 4;
	}
	else if ((*state)->argv[i] == IND_CODE)
	{
		(*state)->f_argv[i] = (parser->code[parser->pos] << 8 |\
		parser->code[parser->pos + 1]);
		parser->pos += 2;
	}
	else
	{
		(*state)->f_argv[i] = parser->code[parser->pos];
		parser->pos++;
	}
}

void	ft_and(t_parser *parser, t_state **state)
{
	(*state)->argv[0] = ft_args(parser, 6);
	(*state)->argv[1] = ft_args(parser, 4);
	(*state)->argv[2] = ft_args(parser, 2);
	if ((*state)->argv[2] != REG_CODE)
		ft_exit("ERROR OPERATION CODE\n");
	parser->pos++;
	ft_and_help(parser, state, 0);
	ft_and_help(parser, state, 1);
	(*state)->f_argv[2] = parser->code[parser->pos];
	(*state) = (*state)->next;
	parser->pos++;
}
