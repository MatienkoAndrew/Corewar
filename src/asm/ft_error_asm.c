/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:58 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/24 15:02:11 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	metka_error(t_metka *metka)
{
	ft_printf("No such label \'%s\' while "\
	"attempting to derefence token at [%d:%d]\n", metka->name,
			metka->link->row, metka->link->column + 1);
	exit(1);
}

void	operator_error(t_cont *cont)
{
	ft_printf("Unexpected operator \'%s\' at [%d:%d]",
			cont->content, cont->row, cont->column);
	exit(1);
}

void	argument_error(t_op *op, t_cont *cont, int count)
{
	ft_printf("Invalid type of %d parameter for instruction \'%s\' at [%d:%d]",
			count, op->name, cont->row, cont->column);
	exit(1);
}

void	lexical_error(t_asm *assem)
{
	ft_printf("Lexical error at [%d:%d]\n", assem->row, assem->column + 1);
	exit(1);
}

void	ft_error_asm(t_cont *content)
{
	ft_printf("Syntax error at token %s \"%s\" at [%d:%d]\n",
			g_types[content->type], content->content,
			content->row, content->column + 1);
	exit(1);
}
