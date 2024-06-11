# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchapard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 15:50:00 by lchapard          #+#    #+#              #
#    Updated: 2024/02/22 11:12:54 by lchapard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = ./src/main.c ./src/actions.c ./src/getters.c ./src/inits.c ./src/lone.c \
./src/mutex_do.c ./src/setters.c ./src/utils.c
HEADERS = ./include/main.h
OBJS = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $^ $(CFLAGS) -pthread -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
