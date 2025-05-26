/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:15:38 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/05/26 16:58:29 by pmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//________________________________________________________________
//|_____________________________[LIBS]____________________________|
//|_______________________________________________________________|

# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>

//________________________________________________________________
//|_________________________[DEFINE COLORS]_______________________|
//|_______________________________________________________________|

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define BLUE "\033[0;36m"
# define DEFAULT_COLOR "\033[0m"

//________________________________________________________________
//|________________________[DEFINE MESSAGES]______________________|
//|_______________________________________________________________|

//------------------ HEADERS MESSAGES

# define TOP_HUD "\n========================[CUB3D]=============\
=============\n\n"
# define BOT_HUD "==============================================\
===========\n\n"

//------------------- ERROR MESSAGES
#define ERROR BLUE TOP_HUD RED "Error:\n" DEFAULT_COLOR \
"%s\n\n" BLUE BOT_HUD DEFAULT_COLOR
# define ERROR_ARGC BLUE "Invalid argument numbers. Usage:\
 ./cub3D [map]"
# define ERROR_FILE_PATH_INVALID "Invalid file path."

//________________________________________________________________
//|________________________[DEFINE OTHERS]________________________|
//|_______________________________________________________________|

# define FILE_EXTENSION ".cub"
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 945
# define TEXTURE_N "./textures/n.xpm"
# define TEXTURE_S "./textures/s.xpm"
# define TEXTURE_E "./textures/e.xpm"
# define TEXTURE_W "./textures/w.xpm"
# define N 0
# define S 1
# define E 2
# define W 3

//________________________________________________________________
//|_____________________________[ENUMS]___________________________|
//|_______________________________________________________________|

typedef enum {
	ZERO = '0',
	ONE = '1',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	SPACE = ' ',
	TAB = '	'
}	map_char;

//________________________________________________________________
//|________________________[DATA STRUCTURES]______________________|
//|_______________________________________________________________|

typedef struct s_position
{
	int						x;
	int						y;
}	t_position;

/* typedef struct s_tile
{
	map_char 				type;
	t_position			 	pos;
	
}t_tile; 
se precisarmos de fazer track a algum elemento em particular em relacao ao seu tipo e posicao e.x sprites animados
*/

typedef struct s_scene
{
	char					**map; 			//layout do mapa passa para esta struct
	t_position				map_size;		//largura e altura do mapa
	t_position				spawn;			//posicao do spawn do player
	char					player_dir;		//N,S,E ou W para a direcao do raycast
	char					*n_path;		//textura desta direcao para passar p MiniLibx 
	char					*s_path;		//textura desta direcao para passar p MiniLibx
	char					*e_path;		//textura desta direcao para passar p MiniLibx
	char					*w_path;		//textura desta direcao para passar p MiniLibx
	int						sky_color;
	int						floor_color;
}	t_scene

typedef struct s_img
{
	void					*mlx_img;
	char					*addr;
	int						bpp;
	int						line_len;
	int						endian;
	int						width;
	int						height;
}	t_img;

typedef struct s_game
{
	t_scene					*scene;			//pointer para a struct do mapa
	void					*mlx;			//instancia mlx
	void					*window;		//janelinha

	t_img					wall[4];		//carregar as imagens das texturas para renderizar dps
	t_img					game_img;
}	t_game;


//________________________________________________________________
//|______________________[FUNCTION PROTOTYPES]____________________|
//|_______________________________________________________________|

//EXECUTOR
bool	render_background(t_game *game);
int		render(t_game *game);
bool	executor(t_game *game, t_data *data);
bool	get_walls(t_game *game);
bool	init_game_data(t_game *game, t_data *data);
void	put_pixel(t_game *game, int x, int y, int color);


//MAP PARSING
bool 	map_char_parser(char *path);

//FREE UTILS
void	free_array(char **arr);

#endif