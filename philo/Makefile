# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/20 00:00:00 by mgumienn          #+#    #+#              #
#    Updated: 2025/12/20 13:06:44 by mgumienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I.

# Lista plików źródłowych - łatwo podmienić *.c na konkretne nazwy
SRCS = $(wildcard *.c)
# Alternatywnie, gotowe do podmiany na:
# SRCS = philosophers.c validation.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re norm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRCS) philosophers.h || true
