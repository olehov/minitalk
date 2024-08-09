# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 10:08:59 by ogrativ           #+#    #+#              #
#    Updated: 2024/08/09 13:24:41 by ogrativ          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFTDIR = ./ft_libft
LIBFT = ./ft_libft/libft_ft.a

all: makelibft $(SERVER) $(CLIENT)

$(CLIENT):
	$(CC) $(CFLAGS) client.c $(LIBFT) -o client

$(SERVER):
	$(CC) $(CFLAGS) server.c $(LIBFT) -o server

makelibft:
	@make -C $(LIBFTDIR)

clean:
	@cd $(LIBFTDIR) && make clean
	
fclean: clean
	@rm -f $(CLIENT)
	@rm -f $(SERVER)
	
re: fclean all

.PHONY: all makeprintf makegnl clean fclean re
