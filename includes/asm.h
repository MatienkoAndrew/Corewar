/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:51:08 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/21 19:51:10 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "ft_printf.h"
# include "op.h"

# define MEMORY "Not allocated memory"
# define MAGIC_HEADER 4
# define CHAMPION_NAME PROG_NAME_LENGTH
# define NULL_CW 4
# define CHAMPION_EXEC_CODE_SIZE 4
# define CHAMPION_COMMENT COMMENT_LENGTH

typedef enum
{
	false,
	true
}	t_bool;

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;

static	char 	*types[] =
{
	"COMMAND",
	"STRING",
	"LABEL",
	"OPERATOR",
	"REGISTER",
	"DIRECT",
	"DIRECT_LABEL",
	"INDIRECT",
	"INDIRECT_LABEL",
	"SEPARATOR",
	"NEW_LINE",
	"END"
};

typedef struct		s_link
{
	int 			row;
	int 			column;
	int 			byte_pos;
	int 			arg_byte;
	int 			size;
	struct s_link	*next;
}					t_link;

typedef struct		s_metka
{
	char			*name;
	int				byte;
	t_link			*link;
	struct s_metka  *next;
}					t_metka;

typedef struct		s_cont
{
	int 			row;
	int 			column;
	char 			*content;
	t_type 			type;
	struct s_cont	*next;
}					t_cont;

typedef struct		s_asm
{
	int 			fd;
	int 			row;
	int 			column;
	int 			byte_pos;
	int 			b_code_size;
	int 			arg_byte;
	char 			*b_code;
	char 			*name;
	char 			*comment;
	t_cont			*content;
	t_metka         *metka;
}					t_asm;

typedef struct	s_op
{
	char		*name;
	int			code;
	int			args_num;
	t_bool		args_types_code;
	int			args_types[3];
	int			t_dir_size;
}				t_op;

/*
** Array
*/

static t_op		g_op[16] = {
{
				.name = "live",
 				.code = 0x01,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 4,
},
{
				.name = "ld",
				.code = 0x02,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.t_dir_size = 4,
},
{
				.name = "st",
				.code = 0x03,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_REG, T_REG | T_IND, 0},
				.t_dir_size = 4,
},
{
				.name = "add",
				.code = 0x04,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG, T_REG},
				.t_dir_size = 4,
},
{
				.name = "sub",
				.code = 0x05,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG, T_REG},
				.t_dir_size = 4,
},
{
				.name = "and",
				.code = 0x06,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
},
{
				.name = "or",
				.code = 0x07,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
},
{
				.name = "xor",
				.code = 0x08,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
},
{
				.name = "zjmp",
				.code = 0x09,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
},
{
				.name = "ldi",
				.code = 0x0A,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.t_dir_size = 2,
},
{
				.name = "sti",
				.code = 0x0B,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
				.t_dir_size = 2,
},
{
				.name = "fork",
				.code = 0x0C,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
},
{
				.name = "lld",
				.code = 0x0D,
				.args_num = 2,
				.args_types_code = true,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.t_dir_size = 4,
},
{
				.name = "lldi",
				.code = 0x0E,
				.args_num = 3,
				.args_types_code = true,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.t_dir_size = 2,
},
{
				.name = "lfork",
				.code = 0x0F,
				.args_num = 1,
				.args_types_code = false,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
},
{
				.name = "aff",
				.code = 0x10,
				.args_num = 1,
				.args_types_code = true,
				.args_types = {T_REG, 0, 0},
				.t_dir_size = 4,
}
};


void				assembler(char *file_name);
t_asm				*initialization(int fd);
void				validation(t_asm *assem);
t_cont				*init_content(t_asm *assem, t_type type);
void				parser_another(t_asm *assem, char *line, int start, t_cont *cont);
void				parser_string(t_asm *assem, char **line, int col, t_cont *cont);
void				new_line(char **line, char *end, int col);
void				new_info(t_asm *assem, char *line);
void				parser_symb(t_asm *assem, char *line, int col, t_cont *cont);
int 				is_registr(const char *str);
int 				is_conditions(char c);
void				add_content(t_asm **assem, t_cont *content);
int					is_help(char c);
void				get_name_comment(t_asm *assem);
void				ft_error_asm(t_cont *content);
void				crypting(t_asm *assem);
void				crypt_label(t_asm *assem, t_cont **content);
void				new_metka(t_metka **metka, t_metka *new);
t_metka				*init_metka(char *name, int point);
t_metka				*metka_exist(t_metka *metka, char *name);
void				crypt_operator(t_asm *assem, t_cont **content);
signed char			get_type(t_type type);
t_op				*get_operation(char *name);
void				convert_to_hex_asm(int nbr, char *b_code, int pos, int size);
void				new_link(t_link **link, t_link *new);
t_link				*init_link(t_asm *assem, t_cont *content, int size);
void				crypt_links(t_asm *assem);
void				new_filename(char **filename, int *fd);
void				write_bytecode(int fd, t_asm *assem);
void				lexical_error(t_asm *assem);
int					start_condition(t_cont *cont);
void				argument_error(t_op *op, t_cont *cont, int count);
void				operator_error(t_cont *cont);

#endif
