/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:22:24 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/23 21:22:33 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	get_comment(t_asm *assem, t_cont **content)
{
	char 	*comment;

	comment = NULL;
	*content = (*content)->next;
	if ((*content)->type == STRING)
	{
		if (!(comment = ft_strsub((*content)->content, 1, ft_strlen((*content)->content) - 2)))
			error("Not allocated memory");
		if (ft_strlen(comment) > COMMENT_LENGTH)
			error("Comment's length is too big\n");
		assem->comment = ft_strdup(comment);
		ft_strdel(&comment);
		*content = (*content)->next;
		if ((*content)->type != NEW_LINE)
			ft_error_asm(*content);
	}
	else
		ft_error_asm(*content);
}

void	get_name(t_asm *assem, t_cont **content)
{
	char 	*name;

	name = NULL;
	*content = (*content)->next;
	if ((*content)->type == STRING)
	{
		if (!(name = ft_strsub((*content)->content, 1, ft_strlen((*content)->content) - 2)))
			error("Not allocated memory");
		if (ft_strlen(name) > PROG_NAME_LENGTH)
			error("Name's length is more than need\n");
		assem->name = ft_strdup(name);
		ft_strdel(&name);
		*content = (*content)->next;
		if ((*content)->type != NEW_LINE)
			ft_error_asm(*content);
	}
	else
		ft_error_asm(*content);
}

void	get_name_comment(t_asm *assem)
{
	t_cont	*content;

	content = assem->content;
	while (assem->name == NULL || assem->comment == NULL)
	{
		if (content->type == COMMAND && !assem->name && !ft_strcmp(content->content, NAME_CMD_STRING))
			get_name(assem, &content);
		else if (content->type == COMMAND && !assem->comment && !ft_strcmp(content->content, COMMENT_CMD_STRING))
			get_comment(assem, &content);
		else
			ft_error_asm(content);
		content = content->next;
	}
}