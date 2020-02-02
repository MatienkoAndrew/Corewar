# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 16:09:18 by fgeruss           #+#    #+#              #
#    Updated: 2020/01/21 19:17:25 by fgeruss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror -c

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = libft.h get_next_line.h ft_printf.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

INCLUDES = -I $(HEADERS_DIRECTORY)

SRC_DIRECTORY = ./src/
C_FILE = ft_atoi.c \
		 ft_memset.c \
		 ft_putnbr.c \
		 ft_putchar.c \
		 ft_strdel.c \
		 ft_strjoin.c \
		 ft_strnew.c \
		 ft_strstr.c \
		 ft_strdup.c \
		 ft_strlen.c \
		 ft_strchr.c \
		 ft_putstr.c \
		 ft_strcmp.c \
		 ft_isdigit.c \
		 get_next_line.c \
		 ft_printf.c \
		 attribute.c \
		 printing.c \
		 print_s.c \
		 print_c.c \
		 print_d.c \
		 initialize.c \
		 digits_nbr.c \
		 print_o.c \
		 print_x.c \
		 print_u.c \
		 print_f1.c \
		 print_e.c \
		 print_e_help.c \
		 print_e_other.c \
		 print_e_other_1.c \
		 print_e_other_2.c \
		 print_e_presicion.c \
		 for_norm.c \
		 ft_bzero.c \
		 ft_itoa.c \
		 ft_strnew_float.c \
		 ft_strsub.c \
		 ft_isalnum.c \
		 ft_isalpha.c ft_putendl_fd.c ft_strchr_asm.c ft_memdel.c ft_strjoin_asm.c ft_error.c ft_memcpy.c

SRC = $(addprefix $(SRC_DIRECTORY, $(C_FILE))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(C_FILE))
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

 #=====COLOUR========
 RED = \033[1;31m
 GREEN = \033[0;32m
 BLUE = \033[34;1m
 YELLOW = \033[0;33m
 RESET = \033[0m
 #===================

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "\n$(GREEN)(•̀ᴗ•́)و $(NAME) generated!"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"
	@echo "$(YELLOW)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling library... Wait a sec."

$(OBJECTS_DIRECTORY)%.o: $(SRC_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(RED)$(NAME): $(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(RED)$(NAME): object files were deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)$(NAME): $(NAME) was deleted$(RESET)"

re: fclean all

