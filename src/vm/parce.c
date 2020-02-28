/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:49:42 by asusan            #+#    #+#             */
/*   Updated: 2020/01/22 22:49:43 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char			*give_string(int fd, ssize_t len, t_vm *vm)
{
	char	*name;

	if (!(name = ft_strnew(len)))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	if (read(fd, name, len) < len)
		error_1(ERROR_NAME_COMMENT, vm);
	return (name);
}

unsigned char	*give_code(int fd, ssize_t len, t_vm *vm)
{
	unsigned char	*name;
	unsigned char	byte;

	if (!(name = malloc(len)))
		error_1(NOT_ALLOCATE_MEMORY, vm);
	if (read(fd, name, len) < len || read(fd, &byte, 1) != 0)
		error_1(ERROR_NAME_COMMENT, vm);
	return (name);
}

t_player		*create_player(t_vm *vm, char *name)
{
	int			fd;
	t_player	*player;

	base_install_player(&player, vm);
	if ((fd = open(name, O_RDONLY)) < 0)
		error_1(ERROR_FILE, vm);
	if (give_number(fd, vm) != COREWAR_EXEC_MAGIC)
		error_1(ERROR_MAGIC_HEADER, vm);
	player->name = give_string(fd, PROG_NAME_LENGTH, vm);
	if (give_number(fd, vm) != 0)
		error_1(ERROR_NOT_NULL, vm);
	if ((player->code_size = give_number(fd, vm)) > CHAMP_MAX_SIZE)
		error_1(ERROR_CHAMP_SIZE, vm);
	player->comment = give_string(fd, COMMENT_LENGTH, vm);
	if (give_number(fd, vm) != 0)
		error_1(ERROR_FILE, vm);
	player->code = give_code(fd, player->code_size, vm);
	close(fd);
	return (player);
}

void			inside_the_cycle(t_vm *vm, char *av, int *count)
{
	t_player	*player;

	if (vm->player == NULL && check_name(av) && vm->flags.n[*count] == 1)
		vm->player = create_player(vm, av);
	else if (check_name(av) && vm->flags.n[*count] == 1)
	{
		player = create_player(vm, av);
		create_player_list(vm, &player);
	}
	if (check_name(av))
		(*count)++;
}

void			parce(t_vm *vm, int ac, char **av)
{
	int			i;
	int			count;
	int			j;

	base_install_vm(vm);
	count_players(ac, av, vm);
	check_duplicate(vm);
	j = 0;
	while (++j != ac)
	{
		i = 0;
		count = 0;
		while (++i < ac)
			inside_the_cycle(vm, av[i], &count);
		all_val_down(&vm->flags.n, vm->count_players);
	}
	vm->last_player_who_live = vm->count_players;
	if (vm->count_players > 4 || vm->count_players < 1)
		error_1(ERROR_COUNT_CHAMP, vm);
	print_players(vm);
}
