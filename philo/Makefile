# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 09:00:14 by yyudi             #+#    #+#              #
#    Updated: 2025/08/30 19:13:50 by yyudi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

INC		= -Iinclude
SRC_DIR	= src

SRCS	= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/monitor.c \
		  $(SRC_DIR)/eatcycle.c \
		  $(SRC_DIR)/routine.c \
		  $(SRC_DIR)/parse.c \
		  $(SRC_DIR)/time.c \
		  $(SRC_DIR)/print.c \
		  $(SRC_DIR)/sim.c \
		  $(SRC_DIR)/utils.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
