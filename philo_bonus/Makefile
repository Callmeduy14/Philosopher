# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 09:01:21 by yyudi             #+#    #+#              #
#    Updated: 2025/08/30 09:01:24 by yyudi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

INC		= -Iinclude
SRC_DIR	= src

SRCS	= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/parse_time.c \
		  $(SRC_DIR)/shared.c \
		  $(SRC_DIR)/child.c \
		  $(SRC_DIR)/parent.c

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
