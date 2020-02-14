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
# include "op_1.h"

# define MEMORY "Not allocated memory"
# define MAGIC_HEADER 4
# define CHAMPION_NAME PROG_NAME_LENGTH
# define NULL_CW 4
# define CHAMPION_EXEC_CODE_SIZE 4
# define CHAMPION_COMMENT COMMENT_LENGTH

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

typedef struct		s_link
{
	int				row;
	int				column;
	int				byte_pos;
	int				arg_byte;
	int				size;
	struct s_link	*next;
}					t_link;

typedef struct		s_metka
{
	char			*name;
	int				byte;
	t_link			*link;
	struct s_metka	*next;
}					t_metka;

typedef struct		s_cont
{
	int				row;
	int				column;
	char			*content;
	t_type			type;
	struct s_cont	*next;
}					t_cont;

typedef struct		s_asm
{
	int				fd;
	int				row;
	int				column;
	int				byte_pos;
	int				b_code_size;
	int				arg_byte;
	char			*b_code;
	char			*name;
	char			*comment;
	t_cont			*content;
	t_metka			*metka;
}					t_asm;

void				assembler(char *file_name);
t_asm				*initialization(int fd);
void				validation(t_asm *assem);
t_cont				*init_content(t_asm *assem, t_type type);
void				parser_another(t_asm *assem,
		char *line, int start, t_cont *cont);
void				parser_string(t_asm *assem, char **line,
		int col, t_cont *cont);
void				new_line(char **line, char *end, int col);
void				new_info(t_asm *assem, char *line);
void				parser_symb(t_asm *assem, char *line,
		int col, t_cont *cont);
int					is_registr(const char *str);
int					is_conditions(char c);
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
void				convert_to_hex_asm(int nbr, char *b_code,
		int pos, int size);
void				new_link(t_link **link, t_link *new);
t_link				*init_link(t_asm *assem, t_cont *content, int size);
void				crypt_links(t_asm *assem);
void				new_filename(char **filename, int *fd);
void				write_bytecode(int fd, t_asm *assem);
void				lexical_error(t_asm *assem);
int					start_condition(t_cont *cont);
void				argument_error(t_op *op, t_cont *cont, int count);
void				operator_error(t_cont *cont);
void				metka_error(t_metka *metka);
void				freeer(t_asm *assem);
void				free_in_assem(t_asm *assem,
		t_metka *temp_m, t_link *temp_l);
signed char			crypt_arguments(t_asm *assem, t_cont **content, t_op *op);
signed char			crypt_argument(t_asm *assem, t_cont **content,
		t_op *op, int count);
void				crypt_number(t_asm *assem, t_cont *content, t_op *op);
void				crypt_register(t_asm *assem, t_cont *content);
void				crypt_direct(t_asm *assem, t_cont *content, int size_arg);
signed char			renew_buffer(signed char b_code_args,
								int count_arg, signed char type);
signed char			get_type_arg(signed char type);
int					start_condition_1(t_cont *cont, char c);

#endif
