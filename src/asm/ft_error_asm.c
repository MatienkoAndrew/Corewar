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

void 	ft_error_asm(t_cont *content)
{
	ft_printf("Syntax error at token %s \"%s\" at [%d:%d]\n", types[content->type],
			content->content, content->row, content->column);
	exit(1);
}