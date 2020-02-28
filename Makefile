# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 17:40:37 by fgeruss           #+#    #+#              #
#    Updated: 2020/02/27 20:10:02 by asusan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_NAME = asm

VM_NAME = corewar

DASM_NAME = dasm

CC = gcc

FLAGS = -Wall -Werror -Wextra

# Libraries and includes

LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/
LIBFT =$(LIBFT_DIRECTORY)libft.a

ASM_LIBRARIES =  -L ./libft/ -lft
ASM_INCLUDES = -I $(HEADER_DIRECTORY) -I $(LIBFT_HEADERS)


VM_LIBRARIES =  -L ./libft/ -lft
VM_INCLUDES = -I $(HEADER_DIRECTORY) -I $(LIBFT_HEADERS)

DASM_LIBRARIES =  -L ./libft/ -lft
DASM_INCLUDES = -I $(HEADER_DIRECTORY) -I $(LIBFT_HEADERS)

# Header

HEADER_DIRECTORY = ./includes/

# dasm

DASM_HEADERS_LIST = asm_error.h dasm.h
DASM_HEADERS = $(addprefix $(HEADER_DIRECTORY), $(DASM_HEADERS_LIST))

# Sources

DASM_SOURCES_DIRECTORY = ./src/dasm/
DASM_SOURCES_LIST = main.c init.c magic_header.c byte_code.c \
            byte_code_1.c byte_code_2.c byte_code_3.c \
            write_to_file.c free_struct.c help.c \
            oper.c oper1.c oper2.c help_write_to_file.c
DASM_SOURCES = $(addprefix $(DASM_SOURCES_DIRECTORY), $(DASM_SOURCES_LIST))

# vm

VM_HEADERS_LIST = op.h corewar.h
VM_HEADERS = $(addprefix $(HEADER_DIRECTORY), $(VM_HEADERS_LIST))

# Sources

VM_SOURCES_DIRECTORY = ./src/vm/
VM_SOURCES_LIST = main.c \
				   parce.c \
				   installers.c \
				   error_1.c \
				   maths.c \
				   cursor.c \
				   free.c \
				   counters.c \
				   checks.c \
				   printing.c \
				   war.c \
				   operations.c \
				   args.c \
				   little_fu.c parce_flags.c killer.c other_installers.c operations_1.c \
				   operations_2.c operations_3.c
VM_SOURCES = $(addprefix $(VM_SOURCES_DIRECTORY), $(VM_SOURCES_LIST))

# asm

ASM_HEADERS_LIST = op.h asm.h
ASM_HEADERS = $(addprefix $(HEADER_DIRECTORY), $(ASM_HEADERS_LIST))

# Sources

ASM_SOURCES_DIRECTORY = ./src/asm/
ASM_SOURCES_LIST = asm.c \
				   assembler.c \
				   initialization.c \
				   validation.c \
				   parsing.c \
				   helper.c \
				   get_name_comment.c \
				   ft_error_asm.c \
				   crypting.c \
				   crypt_label.c \
				   crypt_operator.c \
				   helper_1.c \
				   link.c \
				   crypt_links.c new_filename.c write_bytecode.c freeer.c crypt_arguments.c
ASM_SOURCES = $(addprefix $(ASM_SOURCES_DIRECTORY), $(ASM_SOURCES_LIST))

# Objects

OBJECTS_DIRECTORY = ./objects/

ASM_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)asm/
ASM_OBJECTS_LIST = $(patsubst %.c, %.o, $(ASM_SOURCES_LIST))
ASM_OBJECTS = $(addprefix $(ASM_OBJECTS_DIRECTORY), $(ASM_OBJECTS_LIST))

VM_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)vm/
VM_OBJECTS_LIST = $(patsubst %.c, %.o, $(VM_SOURCES_LIST))
VM_OBJECTS = $(addprefix $(VM_OBJECTS_DIRECTORY), $(VM_OBJECTS_LIST))

DASM_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)dasm/
DASM_OBJECTS_LIST = $(patsubst %.c, %.o, $(DASM_SOURCES_LIST))
DASM_OBJECTS = $(addprefix $(DASM_OBJECTS_DIRECTORY), $(DASM_OBJECTS_LIST))

HEADER = -I includes/

 #=====COLOUR========
 RED = \033[1;31m
 GREEN = \033[0;32m
 BLUE = \033[34;1m
 YELLOW = \033[0;33m
 RESET = \033[0m
 #===================

all: .PHONY $(ASM_NAME) $(VM_NAME) $(DASM_NAME)

.PHONY:
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(ASM_NAME): $(LIBFT) $(ASM_OBJECTS_DIRECTORY) $(ASM_OBJECTS)
	@$(CC) $(FLAGS) $(ASM_LIBRARIES) $(ASM_INCLUDES) $(ASM_OBJECTS) -o $(ASM_NAME)
	@echo "\n$(GREEN)(•̀ᴗ•́)و $(ASM_NAME) generated!"

$(DASM_NAME): $(LIBFT) $(DASM_OBJECTS_DIRECTORY) $(DASM_OBJECTS)
	@$(CC) $(FLAGS) $(DASM_LIBRARIES) $(DASM_INCLUDES) $(DASM_OBJECTS) -o $(DASM_NAME)
	@echo "\n$(GREEN)(•̀ᴗ•́)و $(DASM_NAME) generated!"

$(VM_NAME): $(LIBFT) $(VM_OBJECTS_DIRECTORY) $(VM_OBJECTS)
	@$(CC) $(FLAGS) $(VM_LIBRARIES) $(VM_INCLUDES) $(VM_OBJECTS) -o $(VM_NAME)
	@echo "\n$(GREEN)(•̀ᴗ•́)و $(VM_NAME) generated!"

$(LIBFT):
	@echo "Create $(LIBFT)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(ASM_OBJECTS_DIRECTORY):
	@mkdir -p $(ASM_OBJECTS_DIRECTORY)
	@echo "$(ASM_NAME): $(GREEN)$(ASM_OBJECTS_DIRECTORY) was created$(RESET)"
	@echo "$(YELLOW)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling asm... Wait a sec."

$(ASM_OBJECTS_DIRECTORY)%.o: $(ASM_SOURCES_DIRECTORY)%.c libft/libft.a $(ASM_HEADERS)
	@$(CC) $(FLAGS) -c $(ASM_INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(DASM_OBJECTS_DIRECTORY):
	@mkdir -p $(DASM_OBJECTS_DIRECTORY)
	@echo "$(DASM_NAME): $(GREEN)$(DASM_OBJECTS_DIRECTORY) was created$(RESET)"
	@echo "$(YELLOW)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling dasm... Wait a sec."

$(DASM_OBJECTS_DIRECTORY)%.o: $(DASM_SOURCES_DIRECTORY)%.c libft/libft.a $(DASM_HEADERS)
	@$(CC) $(FLAGS) -c $(DASM_INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"	

$(VM_OBJECTS_DIRECTORY):
	@mkdir -p $(VM_OBJECTS_DIRECTORY)
	@echo "$(VM_NAME): $(GREEN)$(VM_OBJECTS_DIRECTORY) was created$(RESET)"
	@echo "$(YELLOW)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling vm... Wait a sec."

$(VM_OBJECTS_DIRECTORY)%.o: $(VM_SOURCES_DIRECTORY)%.c libft/libft.a $(VM_HEADERS)
	@$(CC) $(FLAGS) -c $(VM_INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(ASM_NAME): $(RED)object files were deleted$(RESET)"
	@echo "$(DASM_NAME): $(RED)object files were deleted$(RESET)"
	@echo "$(VM_NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	@rm -f $(ASM_NAME)
	@echo "$(ASM_NAME): $(RED)$(ASM_NAME) was deleted$(RESET)"
	@rm -f $(VM_NAME)
	@echo "$(VM_NAME): $(RED)$(VM_NAME) was deleted$(RESET)"
	@rm -f $(DASM_NAME)
	@echo "$(DASM_NAME): $(RED)$(DASM_NAME) was deleted$(RESET)"

re: fclean all
