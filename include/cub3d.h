/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:15:38 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/06/04 23:39:49 by pmachado         ###   ########.fr       */
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

# define ERROR_FILE_PATH_INVALID "Invalid file path."
# define ERROR_FILE_EXTENSION "Invalid file extension. Expected .cub"
# define ERROR_INVALID_ARGS "Invalid argument. Usage: ./cub3D [map]"
# define ERROR_NBR_ARGS "Error: Invalid number of arguments\n"
# define ERROR_INVALID_EXTENSION "Error: Invalid file extension\n"
# define ERROR_MALLOC "Error: Memory allocation failed\n"
# define ERROR_FD "Error: Invalid fd\n"
# define ERROR_MLX_INIT "Error: MLX initialization failure\n"
# define ERROR_MAP_PROCESSING "Error processing map\n"
# define ERROR_MAP_INVALID "Error: Invalid map\n"
# define ERROR_MAP_PATH "Error: Path is invalid\n"

# define ERROR_MISS_ELEMTS "Error: Missing required elements"
# define ERROR_DUPLICATE_ELEMENT "Error: Duplicate element in .cub file"
# define ERROR_UNKNOWN_ELEMENT "Error: Unknown identifier in .cub file"
# define ERROR_EMPTY_FILE "Error: File is empty"
# define ERROR_MAP_NOT_CLOSED "Error: Map is not closed"
# define ERROR_PLAYER_NOT_FOUND "Error: Player start position not found"
# define ERROR_INVALID_COLOR "Error: Invalid RGB color format"

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
	char					**raw_lines;	// Copia das linhas do ficheiro .cub
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
//bool	get_walls(t_game *game);
//bool	init_game_data(t_game *game, t_data *data);
void	put_pixel(t_game *game, int x, int y, int color);


//VALIDATION
bool		ft_validate_args(int ac, char **av);
//INITIATE STRUCTS
t_game		*ft_init_game(char *path);
t_game		*ft_create_game(void);
void		ft_init_mlx(t_game *game);
//PARSING
void		check_scene(char *path, t_scene *scene);
void		read_scene(char *path, t_scene *scene);
void		check_for_empty(t_scene *scene);
void		separate_map(t_scene *scene);
void		validate_elements(t_scene *scene);
void		validate_map_characters(char **map);

			//----------read_scene-----------//
int			ft_count_lines(char *path);
char		*spaces_for_tabs(char *line);
int			has_tabs(const char *line);
void		change_tabs(const char *line, char *new_line);
			//----------separate_map---------//
int			get_map_start_index(char **lines);
int			count_map_lines(char **lines);
void		copy_map_lines(t_scene *scene, int start, int count);
int			ft_get_max_line_length(char **map);
bool		ft_is_map_line(char *line);
			//----------validate_elements---------//
void		parse_textures(t_scene *scene, char *line);
void		parse_NO(t_scene *scene, char *line);
void		parse_SO(t_scene *scene, char *line);
void		parse_WE(t_scene *scene, char *line);
void		parse_EA(t_scene *scene, char *line);
void		parse_colors(t_scene *scene, char *line);
int			parse_rgb(const char *line);
char		*trim_and_check_digit(char *str);
void		free_rgb_parts(char **arr, char **trimmed);
bool		ft_isdigit_str(char *str);
			//----------validate_map_chars-------//
bool		is_valid_map_char(char c);
			//----------validate_map-------------//
void		pad_map_lines(t_scene *scene);
void		find_player(t_scene *scene);




//ERROR
void	ft_end(int nbr, t_game *g);
void	free_all(t_game *g);
void	free_scene(t_scene *scene);
void	free_array(char **arr, int max);
int		ft_exit(t_game *g);

//FREE UTILS
void	free_array(char **arr);

#endif