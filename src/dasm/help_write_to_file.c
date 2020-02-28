/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_write_to_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:38:09 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/27 18:38:11 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void		ft_write_func_3(t_state *state, int fd)
{
	char	*number;

	number = NULL;
	if (state->argv[2] == DIR_CODE)
	{
		write(fd, " %", ft_strlen(" %"));
		number = ft_itoa(state->f_argv[2]);
		write(fd, number, ft_strlen(number));
	}
	else if (state->argv[2] == REG_CODE)
	{
		write(fd, " r", ft_strlen(" r"));
		number = ft_itoa(state->f_argv[2]);
		write(fd, number, ft_strlen(number));
	}
	else if (state->argv[2] == IND_CODE)
	{
		write(fd, " ", ft_strlen(" "));
		number = ft_itoa(state->f_argv[2]);
		write(fd, number, ft_strlen(number));
	}
	free(number);
}
