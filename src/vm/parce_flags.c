/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:09:48 by asusan            #+#    #+#             */
/*   Updated: 2020/02/14 16:09:50 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	first_inside(t_vm *vm, char **av, int *i)
{
	vm->flags.dump_val = check_overval(av[(*i) + 1], vm);
	vm->flags.d++;
	(*i)++;
}

void	second_inside(t_vm *vm, char **av, int *i)
{
	vm->flags.dump_val = check_overval(av[(*i) + 1], vm);
	vm->flags.dump++;
	(*i)++;
}

int		flag_n(t_vm *vm, char **av, int ac, int i)
{
	if (!ft_strcmp(av[i], "-n") && i + 2 < ac &&
	ft_strlen(av[i + 1]) == 1 &&
	*av[i + 1] - 48 <= vm->count_players &&
	check_name(av[i + 2]) && *av[i + 1] - 48 > 0)
		return (1);
	return (0);
}

void	third_inside(t_vm *vm, char **av, int *i, int count)
{
	vm->flags.n[count] = *av[(*i) + 1] - 48;
	vm->flags.count_n++;
	(*i)++;
}

void	check_flags(int ac, char **av, t_vm *vm)
{
	int i;
	int count;

	i = base_install_to_parce_flags(vm, &count);
	while (++i != ac)
	{
		if (!ft_strcmp(av[i], "-d") && i + 1 < ac && check_on_digits(av[i + 1]))
			first_inside(vm, av, &i);
		else if (!ft_strcmp(av[i], "-dump") && i + 1 < ac
		&& check_on_digits(av[i + 1]))
			second_inside(vm, av, &i);
		else if (flag_n(vm, av, ac, i))
		{
			third_inside(vm, av, &i, count);
			continue;
		}
		else if (!ft_strcmp(av[i], "-a"))
			vm->flags.aff = 1;
		else if (check_name(av[i]))
			count++;
		else
			error_1(ERROR_INPUT, vm);
	}
	install_to_chrono(&vm->flags.n, vm->count_players, vm);
}
