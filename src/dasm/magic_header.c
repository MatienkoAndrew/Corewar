/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:35:39 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 21:36:02 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

char			*ft_str(int fd, size_t len)
{
	ssize_t		size;
	char		*buffer;

	if (!(buffer = ft_strnew(len)))
		ft_exit(ERR_STR_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		ft_exit(ERR_READ_FILE);
	if (size < (ssize_t)len)
		ft_exit(ERR_INVALID_FILE);
	return (buffer);
}

uint8_t			*parse_2(int fd, size_t len)
{
	ssize_t		size;
	uint8_t		*buffer;
	uint8_t		byte;

	if (!(buffer = ft_memalloc(len)))
		ft_exit(ERR_STR_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		ft_exit(ERR_READ_FILE);
	if (size < (ssize_t)len || read(fd, &byte, 1) != 0)
		ft_exit(ERR_INVALID_FILE);
	return (buffer);
}

static int32_t	bytecode_to_int32(const uint8_t *bytecode, size_t size)
{
	int32_t		result;
	t_bool		sign;
	int			i;

	result = 0;
	sign = (t_bool)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

static int32_t	parse_1(int fd)
{
	ssize_t		size;
	uint8_t		buffer[4];

	size = read(fd, &buffer, 4);
	if (size == -1)
		ft_exit(ERR_READ_FILE);
	if (size < 4)
		ft_exit(ERR_INVALID_FILE);
	return (bytecode_to_int32(buffer, 4));
}

void			ft_magic_header(t_parser *parser, int fd)
{
	if (parse_1(fd) != COREWAR_EXEC_MAGIC)
		ft_exit(ERR_INVALID_MAGIC);
	parser->name = ft_str(fd, PROG_NAME_LENGTH);
	if (parse_1(fd) != 0)
		ft_exit(ERR_NO_NULL);
	if ((parser->code_size = parse_1(fd)) < 0)
		ft_exit(ERR_INVALID_CODE_SIZE);
	parser->comment = ft_str(fd, COMMENT_LENGTH);
	if (parse_1(fd) != 0)
		ft_exit(ERR_NO_NULL);
	parser->code = parse_2(fd, (size_t)parser->code_size);
}
