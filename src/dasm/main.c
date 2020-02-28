/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:01:57 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/27 00:09:51 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include <fcntl.h>

char			ft_args(t_parser *parser, int count)
{
	if ((parser->code[parser->pos] >> count & 3) == REG_CODE)
		return (REG_CODE);
	else if ((parser->code[parser->pos] >> count & 3) == DIR_CODE)
		return (DIR_CODE);
	else if ((parser->code[parser->pos] >> count & 3) == IND_CODE)
		return (IND_CODE);
	else
		ft_exit("ERROR BYTECODE");
	return (0);
}

void			disassemble(char *filename)
{
	t_parser	*parser;
	t_state		*state;
	t_state		*temp;
	int			fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_exit(ERR_OPEN_FILE);
	parser = init();
	state = ft_init();
	temp = state;
	ft_magic_header(parser, fd);
	bytecode_to_code(parser, &state);
	filename = name_replace(filename);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		ft_exit(ERR_CREATE_FILE);
	ft_write_nc(fd, ".name", parser->name);
	ft_write_nc(fd, ".comment", parser->comment);
	write(fd, "\n", ft_strlen("\n"));
	ft_write(temp, fd, filename);
	free(filename);
	ft_free(&parser, &temp);
}

t_bool			ft_filename(const char *filename, const char *ext)
{
	if (filename && ext && ft_strlen(filename) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(filename, '\0') - ft_strlen(ext), ext));
	else
		return (false);
}

int                main(int argc, char **argv)
{
    if (argc == 2 && ft_filename(argv[1], ".cor"))
        disassemble(argv[1]);
    else
        print_help();
    return (0);
}

