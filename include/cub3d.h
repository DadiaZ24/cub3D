/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:15:38 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/10/21 14:54:23 by ddias-fe         ###   ########.fr       */
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
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
# include <math.h>
# include <limits.h>

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
# define ERROR "\033[0;31mError:\n\033[0m%s\n\n"
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
# define RES 64
# define LEFT 65361
# define RIGHT 65361
# define PI 3.14159265359
# define ROTATE_SPEED 0.05
# define MOVE_SPEED 0.05
# define FOV 0.66

//________________________________________________________________
//|_____________________________[ENUMS]___________________________|
//|_______________________________________________________________|

typedef enum e_map_char
{
	ZERO = '0',
	ONE = '1',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	SPACE = ' ',
	TAB = '	'
}	t_map_char;

//________________________________________________________________
//|________________________[DATA STRUCTURES]______________________|
//|_______________________________________________________________|

typedef struct s_position
{
	int			x;
	int			y;
}	t_position;

typedef struct s_texture
{
	int			texture_x;
	int			texture_y;
	double		wall_x;
	double		step;
	double		texture_pos;
}	t_texture;

typedef struct s_raycast
{
	double		ray_x;
	double		ray_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;
	double		step_x;
	double		step_y;
	double		perp_wall_dist;
	bool		hit;
	bool		side;
	int			map_x;
	int			map_y;
	int			line_height;
	int			start;
	int			end;
	int			wall_dir;
	t_texture	tex;
}	t_raycast;

typedef struct s_fill_data
{
	char		**map;
	int			max_x;
	int			max_y;
}	t_fill_data;

typedef struct s_scene
{
	char		**map;			//layout do mapa
	char		**raw_lines;	// Copia das linhas .cub
	t_position	map_size;		//largura e altura do mapa
	t_position	spawn;			//posicao do spawn do player
	char		player_dir;		//N,S,E ou W para raycast
	char		*n_path;		//textura p MiniLibx 
	char		*s_path;		//textura p MiniLibx
	char		*e_path;		//textura p MiniLibx
	char		*w_path;		//textura p MiniLibx
	int			sky_color;
	int			floor_color;
	t_fill_data	data;
}	t_scene;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_player
{
	float		x;
	float		y;
	double		angle;
	double		dir_x;
	double		dir_y;
	int			move_dir;
	int			strafe_dir;
	int			rotating;
}	t_player;

typedef struct s_game
{
	t_scene		*scene;			//pointer para a struct do mapa
	void		*mlx;			//instancia mlx
	void		*window;		//janelinha
	t_img		wall[4];		//carregar as texturas
	t_img		game_img;
	double		buffer;			//buffer de colisao
	t_raycast	raycast;
	t_player	player;			//struct do player
}	t_game;

//________________________________________________________________
//|______________________[FUNCTION PROTOTYPES]____________________|
//|_______________________________________________________________|

//EXECUTOR
bool		init_game_data(t_game *game);
void		init_player(t_game *game);
void		get_player_angle(t_game *game);
void		dda(t_game *game);
void		calculate_distance(t_game *game);
void		rotate(t_game *game, double angle);
void		movement(t_game *game);
void		move_front_right(t_game *game, double x, double y);
void		move_back_left(t_game *game, double x, double y);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		setup_raycast(t_game *game, int x);
void		raycast(t_game *game);
int			draw_loop(t_game *game);

//VALIDATION
bool		ft_validate_args(int ac, char **av);

//INITIATE STRUCTS
t_game		*ft_init_game(char *map_path);
t_game		*ft_create_game(void);
void		ft_init_mlx(t_game *game);
t_scene		*ft_create_scene(char *path, t_game *game);
void		ft_load_textures(t_game *game);

//PARSING
void		check_scene(char *path, t_game *game);
void		read_scene(char *path, t_game *game);
void		check_for_empty(t_game *game);
void		separate_map(t_game *game);
void		validate_elements(t_game *game);
void		validate_map_characters(t_game *game);
void		validate_map(t_game *game);
void		free_duplicate_map(char **arr);

			//----------read_scene-----------//
int			ft_count_lines(char *path);
char		*process_scene_line(char *line);
char		*spaces_for_tabs(char *line);
int			has_tabs(const char *line);
void		change_tabs(const char *line, char *new_line);
bool		all_elements_found(t_scene *scene);

			//----------separate_map---------//
int			get_map_start_index(char **lines);
int			count_map_lines(char **lines);
void		copy_map_lines(t_game *game, int start, int count);
int			ft_get_max_line_length(char **map);
bool		ft_is_map_line(char *line);

			//----------validate_elements---------//
void		parse_textures(t_game *game, char *line);
void		parse_no(t_game *game, char *line);
void		parse_so(t_game *game, char *line);
void		parse_we(t_game *game, char *line);
void		parse_ea(t_game *game, char *line);
void		parse_colors(t_game *game, char *line);
int			parse_rgb(const char *line);
char		*trim_and_check_digit(char *str);
void		free_rgb_parts(char **arr, char **trimmed);
bool		ft_isdigit_str(char *str);
bool		validate_texture_path(char *path);

			//----------validate_map_chars-------//
bool		is_valid_map_char(char c);

			//----------validate_map-------------//
//void		pad_map(t_scene *scene);
void		find_player(t_game *game);
void		set_spawn(t_scene *scene, int x, int y, char dir);
void		replace_spaces_with_1s(char **map);
void		check_closed_map(t_game *game);
char		**duplicate_map(t_game *game);
void		flood_fill(int x, int y, t_game *game);
void		check_player_space(t_game *game);

//ERROR
void		ft_end(int nbr, t_game *g);
void		free_all(t_game *g);
void		free_scene(t_scene *scene);
void		free_array(char **arr, int max);
void		rgb_error(char **colors);
int			ft_exit(t_game *g);

//FREE UTILS
// void	free_array(char **arr);

void		put_pixel(t_game *game, int x, int y, int color);
int			get_color(t_game *game, int x, int y, int i);
bool		render_background(t_game *game);
int			draw_loop(t_game *game);

#endif