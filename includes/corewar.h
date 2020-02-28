/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:58:22 by asusan            #+#    #+#             */
/*   Updated: 2020/01/22 16:58:23 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "../libft/includes/ft_printf.h"

# define ERROR_FILE			"OMG.... WHAT IS IT????"
# define ERROR_MAGIC_HEADER	"Error magic header!"
# define ERROR_NAME_COMMENT	"Invalid player"
# define ERROR_CHAMP_SIZE	"Your player very fat, man"
# define ERROR_COUNT_CHAMP	"I can use 1, 2, 3 or 4 players."
# define NOT_ALLOCATE_MEMORY "Trouble from malloc, man"
# define ERROR_OPERATIONS	"Error operations!"
# define ERROR_INPUT			"Error input parametrs, man"
# define ERROR_FLAGS			"Your flag(s) is(are) bad"
# define ERROR_NOT_NULL		"Player haven't NULL inside bytecode"

typedef struct				s_flags
{
	int						d;
	int						aff;
	int						dump;
	int						dump_val;
	int						count_n;
	int						*n;
}							t_flags;

typedef struct				s_player
{
	int						id;
	char					*name;
	ssize_t					code_size;
	int						cycle_live;
	unsigned char			*code;
	char					*comment;
	struct s_player			*next;
}							t_player;

typedef struct				s_cursor
{
	int						id;
	int						carry;
	unsigned char			first_code;
	int						op_size;
	int						count_cycle_last_live;
	int						count_cycle_to_do;
	int						pos;
	unsigned char			type_args[3];
	int						args_val[3];
	int						regs[REG_NUMBER];
	t_player				*player;
	struct s_cursor			*next;
}							t_cursor;

typedef struct				s_vm
{
	unsigned char			map[MEM_SIZE];
	int						count_players;
	int						last_player_who_live;
	int						cycle_to_die;
	int						count_cursor;
	int						count_cycles_after_check;
	size_t					count_cycles;
	int						count_live;
	int						count_not_deleted;
	int						count_cycles_to_max_checks;
	t_cursor				*cursor;
	t_cursor				*cursor_for_op;
	t_player				*player;
	t_flags					flags;
}							t_vm;

typedef struct				s_options
{
	char					*name;
	int						count_args;
	unsigned char			type_args[3];
	int						change_carry;
	int						code_type_args;
	int						size_dir;
	int						count_cycles;
	void					(*func)(t_vm *);
}							t_options;

void						ft_live(t_vm *vm);
void						ft_ld(t_vm *vm);
void						ft_st(t_vm *vm);
void						ft_add(t_vm *vm);
void						ft_sub(t_vm *vm);
void						ft_and(t_vm *vm);
void						ft_or(t_vm *vm);
void						ft_xor(t_vm *vm);
void						ft_zjmp(t_vm *vm);
void						ft_ldi(t_vm *vm);
void						ft_sti(t_vm *vm);
void						ft_fork(t_vm *vm);
void						ft_lld(t_vm *vm);
void						ft_lldi(t_vm *vm);
void						ft_lfork(t_vm *vm);
void						ft_aff(t_vm *vm);

static	t_options			g_option[16] =
{
	{
		.name = "live",
		.count_args = 1,
		.type_args = {T_DIR, 0, 0},
		.change_carry = 0,
		.code_type_args = 0,
		.size_dir = 4,
		.count_cycles = 10,
		.func = &ft_live
	},
	{
		.name = "ld",
		.count_args = 2,
		.type_args = {T_DIR | T_IND, T_REG, 0},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 5,
		.func = &ft_ld
	},
	{
		.name = "st",
		.count_args = 2,
		.type_args = {T_REG, T_REG | T_IND, 0},
		.change_carry = 0,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 5,
		.func = &ft_st
	},
	{
		.name = "add",
		.count_args = 3,
		.type_args = {T_REG, T_REG, T_REG},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 10,
		.func = &ft_add
	},
	{
		.name = "sub",
		.count_args = 3,
		.type_args = {T_REG, T_REG, T_REG},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 10,
		.func = &ft_sub
	},
	{
		.name = "and",
		.count_args = 3,
		.type_args = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 6,
		.func = &ft_and
	},
	{
		.name = "or",
		.count_args = 3,
		.type_args = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 6,
		.func = &ft_or
	},
	{
		.name = "xor",
		.count_args = 3,
		.type_args = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 6,
		.func = &ft_xor
	},
	{
		.name = "zjmp",
		.count_args = 1,
		.type_args = {T_DIR, 0, 0},
		.change_carry = 0,
		.code_type_args = 0,
		.size_dir = 2,
		.count_cycles = 20,
		.func = &ft_zjmp
	},
	{
		.name = "ldi",
		.count_args = 3,
		.type_args = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.change_carry = 0,
		.code_type_args = 1,
		.size_dir = 2,
		.count_cycles = 25,
		.func = &ft_ldi
	},
	{
		.name = "sti",
		.count_args = 3,
		.type_args = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.change_carry = 0,
		.code_type_args = 1,
		.size_dir = 2,
		.count_cycles = 25,
		.func = &ft_sti
	},
	{
		.name = "fork",
		.count_args = 1,
		.type_args = {T_DIR, 0, 0},
		.change_carry = 0,
		.code_type_args = 0,
		.size_dir = 2,
		.count_cycles = 800,
		.func = &ft_fork
	},
	{
		.name = "lld",
		.count_args = 2,
		.type_args = {T_DIR | T_IND, T_REG, 0},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 10,
		.func = &ft_lld
	},
	{
		.name = "lldi",
		.count_args = 3,
		.type_args = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.change_carry = 1,
		.code_type_args = 1,
		.size_dir = 2,
		.count_cycles = 50,
		.func = &ft_lldi
	},
	{
		.name = "lfork",
		.count_args = 1,
		.type_args = {T_DIR, 0, 0},
		.change_carry = 0,
		.code_type_args = 0,
		.size_dir = 2,
		.count_cycles = 1000,
		.func = &ft_lfork
	},
	{
		.name = "aff",
		.count_args = 1,
		.type_args = {T_REG, 0, 0},
		.change_carry = 0,
		.code_type_args = 1,
		.size_dir = 4,
		.count_cycles = 2,
		.func = &ft_aff
	}
};

/*
** 							*** ARGS.C ***
*/

void						check_args(t_vm *vm, t_cursor *cursor);
int							check_on_valid_args(t_cursor *cursor);

/*
** 							*** CHECKS.C ***
*/

int							check_on_digits(char *arr);
void						check_duplicate(t_vm *vm);
void						check(t_vm *vm);
int							check_name(const char *arr);

/*
** 							*** COUNTERS.C.c ***
*/

int							count_players(int ac, char **av, t_vm *vm);
int							near_zero(const int *arr, int size);

/*
** 							*** CURSOR.C.c ***
*/

void						create_cursor(t_vm *vm);

/*
** 							*** ERROR.C ***
*/

void						error_1(char *message, t_vm *vm);

/*
** 							*** FREE.C ***
*/

void						free_all(t_vm *vm);

/*
** 							*** INSTALLERS.C ***
*/

void						base_install_player(t_player **player, t_vm *vm);
void						base_install_vm(t_vm *vm);
void						install_pos_for_cursor(t_cursor *cursor, t_vm *vm);
int							base_install_to_parce_flags(t_vm *vm, int *count);
void						base_install_to_cursor(t_cursor **cursor,
		t_player *player);

/*
** 							*** KILLER.C ***
*/

void						check_to_die_cursor(t_vm *vm,
		t_cursor **cursor, int id);

/*
** 							*** LITTLE_FU.C ***
*/

int							num_of_flag(t_vm *vm, int count);
int							increment_pos(int val, int count);
int							check_overval(char *arr, t_vm *vm);
void						create_player_list(t_vm *vm, t_player **player);
void						all_val_down(int **arr, int size);

/*
** 							*** MATHS.C ***
*/

int32_t						give_number(int fd, t_vm *vm);
int							give_arg_val(const unsigned char *arr,
		int count_symb, int pos);
void						write_to_map(t_vm *vm, int val, int pos, int size);

/*
** 							*** OTHER_INSTALLERS.C ***
*/

void						install_to_reg(int (*arr)[16], int id);
void						install_to_chrono(int **arr, int size, t_vm *vm);
void						install_to_val(int **arr, int size, int val);
void						install_to_carry(t_vm *vm, int val);

/*
** 							*** PARCE.C ***
*/

void						parce(t_vm *vm, int ac, char **av);

/*
** 							*** PARCE_FLAGS.C ***
*/

void						check_flags(int ac, char **av, t_vm *vm);

/*
** 							*** PRINTING.C ***
*/

void						print_players(t_vm *vm);
void						print_for_ddump(t_vm *vm);
void						print_champ(t_vm *vm);

/*
** 							*** WAR.C ***
*/

void						war(t_vm *vm);

#endif
