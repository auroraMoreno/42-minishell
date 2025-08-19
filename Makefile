# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 09:17:20 by aumoreno          #+#    #+#              #
#    Updated: 2025/08/19 16:41:34 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === Project Config ===
NAME = minishell

SRCS = main.c utils.c signals.c cmd_utils.c \
	builtins/built_ins.c builtins/echo.c builtins/cd.c builtins/pwd.c builtins/export.c builtins/unset.c builtins/env.c builtins/exit.c \
	executer.c executer_utils.c init.c create_pipe.c free_utils.c errors.c 
# pipex/main_bonus.c pipex/pipex_bonus.c pipex/utils_bonus.c

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
