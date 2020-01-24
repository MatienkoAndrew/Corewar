# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 17:40:37 by fgeruss           #+#    #+#              #
#    Updated: 2020/01/24 15:05:51 by fgeruss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_NAME = asm

CC = gcc

FLAGS = -Wall -Werror -Wextra

# Libraries and includes

LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/
LIBFT =$(LIBFT_DIRECTORY)libft.a

ASM_LIBRARIES =  -L ./libft/ -lft
ASM_INCLUDES = -I $(HEADER_DIRECTORY) -I $(LIBFT_HEADERS)

# Header

HEADER_DIRECTORY = ./includes/

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
				   ft_error_asm.c
ASM_SOURCES = $(addprefix $(ASM_SOURCES_DIRECTORY), $(ASM_SOURCES_LIST))

# Objects

OBJECTS_DIRECTORY = ./objects/

ASM_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)asm/
ASM_OBJECTS_LIST = $(patsubst %.c, %.o, $(ASM_SOURCES_LIST))
ASM_OBJECTS = $(addprefix $(ASM_OBJECTS_DIRECTORY), $(ASM_OBJECTS_LIST))

 #=====COLOUR========
 RED = \033[1;31m
 GREEN = \033[0;32m
 BLUE = \033[34;1m
 YELLOW = \033[0;33m
 RESET = \033[0m
 #===================

.PHONY: all clean fclean re

all: $(ASM_NAME)

$(ASM_NAME): $(LIBFT) $(ASM_OBJECTS_DIRECTORY) $(ASM_OBJECTS)
	@$(CC) $(FLAGS) $(ASM_LIBRARIES) $(ASM_INCLUDES) $(ASM_OBJECTS) -o $(ASM_NAME)
	@echo "\n$(GREEN)(•̀ᴗ•́)و $(ASM_NAME) generated!"

$(LIBFT):
	@echo "Create $(LIBFT)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(ASM_OBJECTS_DIRECTORY):
	mkdir -p $(ASM_OBJECTS_DIRECTORY)
	@echo "$(ASM_NAME): $(GREEN)$(ASM_OBJECTS_DIRECTORY) was created$(RESET)"
	@echo "$(YELLOW)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling asm... Wait a sec."

$(ASM_OBJECTS_DIRECTORY)%.o: $(ASM_SOURCES_DIRECTORY)%.c $(ASM_HEADERS)
	@$(CC) $(FLAGS) -c $(ASM_INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(ASM_NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(ASM_NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	@echo "$(ASM_NAME): $(RED)$(FT_PRINTF) was deleted$(RESET)"
	@rm -f $(ASM_NAME)
	@echo "$(ASM_NAME): $(RED)$(ASM_NAME) was deleted$(RESET)"
	@rm -f $(ASM_NAME)
	@echo "$(ASM_NAME): $(RED)$(ASM_NAME) was deleted$(RESET)"

re: fclean all
