/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:53:30 by asusan            #+#    #+#             */
/*   Updated: 2020/01/22 22:53:31 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	error_1(char *message, t_vm *vm)
{
	free_all(vm);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(0);
}
