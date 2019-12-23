# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmariott <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/24 17:09:13 by lmariott          #+#    #+#              #
#    Updated: 2019/12/02 17:05:28 by tdelabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc
CFLAGS = -Wall -Wextra -Werror

#sources
SRC_NAME = main.c parse.c parse_node.c parse_pipe.c bfs.c tools.c\
		   set_pipes_unavailable.c generate_paths.c manage_tab_pipes.c\
		   combine_paths.c combine_paths_utilities.c control_during_bfs.c \
		   print_anthill.c get_paths.c t_combi.c tab_n_ants.c #debug.c
SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))

#libraries
LIB_NAME = libft.a
LIB_DIR = libft/
LIB = $(addprefix $(LIB_DIR), $(LIB_NAME))

#objects
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))

#includes
INC_NAME = lem_in.h
INC_DIR = inc/
INC = $(addprefix $(INC_DIR), $(INC_NAME))

CPPFLAGS = -I$(INC_DIR) -I$(LIB_DIR)$(INC_DIR)

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(LIB) $(INC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(NAME) : $(OBJ_DIR) $(OBJ) $(LIB) tags
	$(CC) $(OBJ) $(LIB) -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(LIB) :
	make -C $(LIB_DIR)

tags :
	ctags $(SRC)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)
	rm tags

re : fclean all

.PHONY : all clean fclean re
