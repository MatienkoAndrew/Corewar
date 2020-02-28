/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:59:22 by asusan            #+#    #+#             */
/*   Updated: 2020/01/22 16:59:24 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_help_1(void)
{
	ft_printf("Usage: ./corewar "
		"[-a (-dump|-d) <num>] [-n <num>] <champion.cor> <...>\n");
	ft_printf("    -a          : "
		"Print output from \"aff\" (Default is off)\n");
	ft_printf("    -dump <num> : "
		"Dump memory (32 octets per line) after <num> cycles and exit\n");
	ft_printf("    -d    <num> : "
		"Dump memory (64 octets per line) after <num> cycles and exit\n");
	ft_printf("    -n    <num> : "
		"Set <num> of the next player\n");
	exit(0);
}

int        main(int argc, char **argv)
{
    t_vm vm;

    if (argc == 1)
        print_help_1();
    parce(&vm, argc, argv);
    create_cursor(&vm);
    war(&vm);
    free_all(&vm);
    return (0);
}

