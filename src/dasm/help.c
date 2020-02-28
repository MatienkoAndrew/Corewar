/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:25:07 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 23:25:08 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	ft_exit(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	exit(1);
}

void	print_help(void)
{
	write(1, "Usage: ./dasm <file.cor>\n",
			ft_strlen("Usage: ./dasm <file.cor>\n"));
	exit(0);
}
