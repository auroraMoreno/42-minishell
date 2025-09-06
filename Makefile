# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 09:17:20 by aumoreno          #+#    #+#              #
#    Updated: 2025/09/06 22:00:42 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === Project Config ===
NAME = minishell

SRCS = 	init.c \
		main.c \
		parser/parser.c \
		parser/lexer/input_to_tokens.c \
		parser/lexer/char_is_functions.c \
		parser/lexer/check_char_functions.c \
		parser/lexer/find_tokens_delimiters.c \
		parser/lexer/tokens_in_list.c \
		parser/grammar/tokens_to_cmds.c	\
		parser/grammar/words.c \
		parser/grammar/redirs.c \
		parser/grammar/quotes.c \
		parser/grammar/print_cmds.c	\
		parser/utils.c	\
		executer.c \
		executer_utils.c \
		builtins/built_ins.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c  \
		builtins/exit.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/pwd.c \
		builtins/unset.c \
		signals.c \
		free_utils.c \
		errors.c \
		utils.c \
 		heredoc.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
# 		heredoc_utils.c 
# 		redir.c 

OBJS = $(SRCS:.c=.o)

# === Libft ===
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# === Compiler/Flags ===
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft
INCLUDES = -I$(LIBFT_DIR)

# === Rules ===

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)" --silent
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(INCLUDES)
	@echo "✔️  Built $(NAME) without AddressSanitizer"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@echo "🧹 Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@echo "🧹 Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
