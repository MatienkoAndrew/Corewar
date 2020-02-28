/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_asm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:57:03 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 20:08:51 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include "op.h"
# include "op_1.h"
# include "asm_error.h"

typedef struct			s_state
{
	char				*name;
	char				argv[3];
	int					f_argv[3];
	struct s_state		*next;
}						t_state;

/*
** Parser
*/

typedef struct			s_parser
{
	char				*name;
	char				*comment;
	int32_t				code_size;
	uint8_t				*code;
	int32_t				pos;
}						t_parser;

/*
** INIT
*/

t_state					*ft_init();
t_parser				*init();

/*
** EXIT
*/

void					ft_exit(char *s);

/*
** NAME AND COMMENT
*/

void					ft_magic_header(t_parser *parser, int fd);
char					*name_replace(char *filename);

/*
** OPERATIONS WITH BYTE_CODE
*/

void					bytecode_to_code(t_parser *parser, t_state **state);
void					ft_aff(t_parser *parser, t_state **state);
void					ft_lld(t_parser *parser, t_state **state);
void					ft_fork(t_parser *parser, t_state **state);
void					ft_ldi(t_parser *parser, t_state **state);
void					ft_ldi_help(t_parser *parser, t_state **state);
void					ft_and(t_parser *parser, t_state **state);
void					ft_and_help(t_parser *parser, t_state **state, int i);
void					ft_sub(t_parser *parser, t_state **state);
void					ft_st(t_parser *parser, t_state **state);
void					ft_add(t_parser *parser, t_state **state);
void					ft_sti(t_parser *parser, t_state **state);
void					ft_live(t_parser *parser, t_state **state);
void					ft_ld(t_parser *parser, t_state **state);
void					ft_zjmp(t_parser *parser, t_state **state);
void					byte_code_zjmp(t_parser *parser, t_state **state);
void					byte_code_st(t_parser *parser, t_state **state);
void					byte_code_add(t_parser *parser, t_state **state);
void					byte_code_sub(t_parser *parser, t_state **state);
void					byte_code_and(t_parser *parser, t_state **state);
void					byte_code_xor(t_parser *parser, t_state **state);
void					byte_code_ldi(t_parser *parser, t_state **state);
void					byte_code_fork(t_parser *parser, t_state **state);
void					byte_code_lld(t_parser *parser, t_state **state);
void					byte_code_or(t_parser *parser, t_state **state);
void					byte_code_lldi(t_parser *parser, t_state **state);
void					byte_code_lfork(t_parser *parser, t_state **state);
void					byte_code_aff(t_parser *parser, t_state **state);
char					ft_args(t_parser *parser, int count);

/*
** WRITE
*/

void					ft_write_nc(int fd, char *s1, char *s);
void					ft_write(t_state *temp, int fd, char *filename);
void					ft_write_func_3(t_state *state, int fd);

/*
** FREE
*/

void					ft_free(t_parser **parser, t_state **state);
void					ft_free_char(char *s1, char *s2);

/*
** HELP
*/

void					print_help(void);
void					ft_exit(char *s);

#endif
