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
MLXFLAGS 		= -L./libs/minilibx-linux -lmlx -L/usr/lib -lm -lXext -lX11
NAME			= cub3D

INC				= -I./include
LIBFT			= libs/libft/libft.a
MLX 			= libs/minilibx-linux/libmlx.a


GENERAL			= main.c

PARSING = \
				args_validation.c \
				errors.c \
				scene_check.c \
				scene_check2.c \
				parsing_utils.c \
				parsing_utils2.c \
				parsing_utils3.c \
				parsing_utils4.c \
				parsing_utils5.c

EXECUTOR		= init.c player.c render.c

UTILS			= render_utils.c

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
					src/executor/app\
					src/executor/map\
					src/executor/utils\

OBJ_DIR			= obj

OBJ 			= $(SRC:%.c=$(OBJ_DIR)/%.o)

# _______________________________________________________________
#|_____________________________[RULES]___________________________|
#|_______________________________________________________________|

all:			$(NAME)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ) $(MLX) $(LIBFT)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "✅ Build complete"

$(LIBFT): libs/libft/*.c
	@echo "Building libft..."
	@$(MAKE) -C libs/libft > /dev/null

$(MLX): 
	@echo "Building MiniLibX..."
	@$(MAKE) -C ./libs/minilibx-linux > /dev/null

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Cleaning executable and libraries..."
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: 			fclean all

valgrind: 
	@valgrind --leak-check=full -s --show-leak-kinds=all --track-fds=yes ./$(NAME)

gdb:
	gdb -tui ./$(NAME)

download:
	@wget https://cdn.intra.42.fr/document/document/32396/minilibx-linux.tgz --no-check-certificate
	@tar -xzf minilibx-linux.tgz -C libs
	@rm minilibx-linux.tgz

.PHONY: 		all clean fclean re
