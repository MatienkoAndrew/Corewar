/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 20:30:20 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/24 20:30:35 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*newptr;

	if (!size && ptr)
	{
		if (!(newptr = (char *)malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (newptr);
	}
	if (!(newptr = (char *)malloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, size);
		ft_memdel(&ptr);
	}
	return (newptr);
}


void	renew_byte_code_buffer(t_asm *assem)
{
//	char 	*temp;
//
//	temp = NULL;
//	assem->b_code_size += CHAMP_MAX_SIZE;
//	if (assem->b_code == NULL)
//	{
//		if (!(assem->b_code = ft_strnew((size_t)assem->b_code_size + 14)))
//			error("Not allocated memory");
//	}
//	else
//	{
////		if (!(temp = ft_strdup(assem->b_code)))
////			error(MEMORY);
//		if (!(temp = ft_strnew((size_t)assem->b_code_size + 14)))
//			error(MEMORY);
//		if (!ft_memcpy(temp, assem->b_code, (size_t)ft_strlen(assem->b_code)))
//			error(MEMORY);
//
//		ft_strdel(&assem->b_code);
//		if (!(assem->b_code = ft_strnew((size_t)assem->b_code_size + 14)))
//			error("Not allocated memory");
//		if (!ft_memcpy(assem->b_code, temp, (size_t)ft_strlen(temp)))
//			error(MEMORY);
//		ft_strdel(&temp);
//	}


	assem->b_code_size += CHAMP_MAX_SIZE;
	if (!(assem->b_code = (char *)ft_realloc(assem->b_code, (size_t)assem->b_code_size + 14)))
		error(MEMORY);




//	assem->b_code_size += CHAMP_MAX_SIZE;
//	if (!(assem->b_code = (char *)realloc(assem->b_code,
//										 ((size_t)assem->b_code_size + 14))))
//		error("awd");
}

int		skip(t_cont *content)
{
	return (content->type == NEW_LINE || \
			content->type == COMMAND || \
			content->type == SEPARATOR || \
			content->type == STRING);
}

void	crypting(t_asm *assem)
{
	t_cont	*content;

	content = assem->content;
	while (content->type != END)
	{
		if (assem->byte_pos >= assem->b_code_size)
			renew_byte_code_buffer(assem);
		assem->arg_byte = assem->byte_pos;
		if (content->type == LABEL)
			crypt_label(assem, &content);
		if (content->type == OPERATOR)
			crypt_operator(assem, &content);
		if (skip(content))
			content = content->next;
	}

}