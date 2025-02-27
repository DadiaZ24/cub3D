# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 16:55:42 by ddias-fe          #+#    #+#              #
#    Updated: 2024/12/10 15:59:07 by ptorrao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# _______________________________________________________________
#|___________________________[VARIABLES]_________________________|
#|_______________________________________________________________|

CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror
NAME			= cub3D

INC				= -I./include
LIBFT			= libs/libft/libft.a

GENERAL			= main.c

PARSING			=

EXECUTOR		=

UTILS			= 

# _______________________________________________________________
#|___________________________[SRC FILES]_________________________|
#|_______________________________________________________________|

SRC				= $(GENERAL)\
					$(PARSING)\
					$(EXECUTOR)\

VPATH 			= src\
					src/parsing\
					src/utils\
					src/executor\

OBJ_DIR			= obj

OBJ 			= $(SRC:%.c=$(OBJ_DIR)/%.o)

# _______________________________________________________________
#|_____________________________[RULES]___________________________|
#|_______________________________________________________________|

all:			$(NAME)

$(OBJ_DIR):
				mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

$(NAME):		$(OBJ_DIR) $(OBJ) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):		libs/libft/*.c
				make -C libs/libft

clean:
				$(RM) $(OBJ_DIR)

fclean: 		clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)

re: 			fclean all

valgrind: 
	@valgrind --leak-check=full -s --show-leak-kinds=all --track-fds=yes ./$(NAME)

gdb:
	gdb -tui ./$(NAME)

download:
	@wget https://cdn.intra.42.fr/document/document/25858/minilibx-linux.tgz --no-check-certificate
	@tar -xzf minilibx-linux.tgz -C libs
	@rm minilibx-linux.tgz

.PHONY: 		all clean fclean re
