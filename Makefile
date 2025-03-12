# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 16:16:15 by joao-ppe          #+#    #+#              #
#    Updated: 2025/03/06 16:16:15 by joao-ppe         ###   ########.fr        #
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

PARSING			= map_parsing.c

EXECUTOR		=

UTILS			= free_utils.c

# _______________________________________________________________
#|___________________________[SRC FILES]_________________________|
#|_______________________________________________________________|

SRC				= $(GENERAL)\
					$(PARSING)\
					$(EXECUTOR)\
					$(UTILS)\

VPATH 			= src\
					src/parsing\
					src/parsing/map\
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
	@wget https://cdn.intra.42.fr/document/document/31395/minilibx-linux.tgz --no-check-certificate
	@tar -xzf minilibx-linux.tgz -C libs
	@rm minilibx-linux.tgz

.PHONY: 		all clean fclean re
