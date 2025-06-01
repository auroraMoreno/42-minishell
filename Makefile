# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 12:53:08 by aumoreno          #+#    #+#              #
#    Updated: 2025/05/17 14:01:15 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = minishell

SRCS = main.c built_ins.c executer.c

LIBFT_PATH = libft/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH)

OBJS = ${SRCS:.c=.o}

$(EXEC): $(OBJS)
	@make -C $(LIBFT_PATH) --silent
	@$(CC) $(CFLAGS) ${SRCS} -o $(EXEC)  -I./libft -L./libft -lft

all: $(EXEC)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean --silent

fclean:  clean
	@$(RM) $(EXEC)
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) fclean --silent
	
re: fclean all

.PHONY: all clean fclean re