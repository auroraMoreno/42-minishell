# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 18:40:03 by ccarro-d          #+#    #+#              #
#    Updated: 2025/08/27 20:26:14 by ccarro-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Exit
NAME = ms_parser

# Folders
CORE_DIR = ..
LIBFT_DIR = $(CORE_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj


# Sources
SRC = 	parser.c					\
		input_to_tokens.c 			\
		char_is_functions.c 		\
		check_char_functions.c		\
		find_tokens_delimiters.c	\
		tokens_in_list.c			\
		utils.c

# Archivos objeto (en /obj)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I$(CORE_DIR) -I$(LIBFT_DIR)

# Build the executable
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "✅ Compilation finished!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Recompile object files if minishell.h changes
$(OBJ): $(CORE_DIR)/minishell.h

# Default target for compilation
all: $(NAME)

# Compilation for every .c to .o in /obj
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create  /obj folder if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean objects (remove /obj folder)
clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objects cleaned!"

# Clean objects and executable
fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Executable cleaned!"

# Clean and recompile everything
re: fclean all

# Sanitizer builds
asan:
	@$(MAKE) fclean
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS) -g -fsanitize=address"

# Valgrind  runs (Linux only)
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all

# Key words
.PHONY: all clean fclean re asan   valgrind
