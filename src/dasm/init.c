/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:27:43 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 21:27:47 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

char			*name_replace(char *filename)
{
	char		*basename;

	basename = ft_strsub(filename, 0, ft_strlen(filename) - ft_strlen(".cor"));
	if (!basename)
		ft_exit(ERR_STR_INIT);
	if (!(filename = ft_strjoin(basename, ".s")))
		ft_exit(ERR_STR_INIT);
	ft_strdel(&basename);
	return (filename);
}

t_parser		*init(void)
{
	t_parser	*parser;

	if (!(parser = (t_parser *)ft_memalloc(sizeof(t_parser))))
		ft_exit(ERR_PARSER_INIT);
	parser->code_size = 0;
	parser->code = 0;
	parser->comment = NULL;
	parser->name = NULL;
	parser->pos = 0;
	return (parser);
}

t_state			*ft_init(void)
{
	t_state *state;

	if (!(state = (t_state *)ft_memalloc(sizeof(t_state))))
		ft_exit(ERR_STATEMENT_INIT);
	state->argv[0] = 0;
	state->argv[1] = 0;
	state->argv[2] = 0;
	state->name = NULL;
	state->next = NULL;
	return (state);
}
