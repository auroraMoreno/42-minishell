# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesar <cesar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 18:40:03 by ccarro-d          #+#    #+#              #
#    Updated: 2025/08/28 19:43:23 by cesar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Exit
NAME = ms_parser

# Folders
CORE_DIR = ..
LIBFT_DIR = $(CORE_DIR)/libft
OBJ_DIR = obj

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Sources
SRC = 	parser.c					\
		input_to_tokens.c 			\
		char_is_functions.c 		\
		check_char_functions.c		\
		find_tokens_delimiters.c	\
		tokens_in_list.c			\
		utils.c

# Objects and dependencies in OBJ_DIR
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

# Compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
INCLUDES = -I$(CORE_DIR) -I$(LIBFT_DIR)

# Readline (activated by default to avoid 'undefined reference to readline')
READLINE ?= 1
UNAME_S := $(shell uname -s)
ifeq ($(READLINE),1)
  ifeq ($(UNAME_S),Darwin)
    BREW_PREFIX      := $(shell brew --prefix 2>/dev/null)
    READLINE_PREFIX  := $(shell brew --prefix readline 2>/dev/null)
    #NCURSES_PREFIX   := $(shell brew --prefix ncurses 2>/dev/null)

    # Includes (if Homebrew is installed)
    ifneq ($(BREW_PREFIX),)
      CFLAGS  += -I$(READLINE_PREFIX)/include -I$(NCURSES_PREFIX)/include
      LDFLAGS += -L$(READLINE_PREFIX)/lib -lreadline \
                 #-L$(NCURSES_PREFIX)/lib  -lncurses
    else
      # Typical fallback in mac ARM
      CFLAGS  += -I/opt/homebrew/opt/readline/include
      LDFLAGS += -L/opt/homebrew/opt/readline/lib -lreadline
    endif
  else
    # Linux (just enough with:)
    LDFLAGS += -lreadline -lncurses
    # If requested by the linker
    # LDFLAGS += -lreadline -lncurses
  endif
endif

# Build the executable
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "✅ Compilation finished!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Recompile object files if minishell.h changes
$(OBJ): $(CORE_DIR)/minishell.h

# Default target for compilation
all: $(NAME)

# Compilation for every .c to .o in /obj
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create  /obj folder if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean objects (remove /obj folder)
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "🧹 Objects cleaned!"

# Clean objects and executable
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
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

# Handy run
run: all
	./$(NAME)

# Key words
.PHONY: all clean fclean re asan valgrind run

# Auto-include headers dependencies generated with -MMD -MP
-include $(DEP)