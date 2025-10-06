/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmachado <pmachado@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:15:38 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/06/07 21:11:19 by pmachado         ###   ########.fr       */
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
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
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
= ============\n\n"
# define BOT_HUD "==============================================\
= ==========\n\n"

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

typedef enum direction
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

typedef struct s_texture
{
	int		texture_x;
	int		texture_y;
	double	wall_x;
	double	step;
	double	texture_pos;
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

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_scene
{
	char		**map;
	char		**raw_lines;
	char		player_dir;
	char		*n_path;
	char		*s_path;
	char		*e_path;
	char		*w_path;
	int			sky_color;
	int			floor_color;
	t_position	map_size;
	t_position	spawn;
}	t_scene;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	float	x;
	float	y;
	double	angle;
	double	dir_x;
	double	dir_y;
	int		move_dir;
	int		strafe_dir;
	int		rotating;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	double		buffer;
	t_scene		*scene;
	t_raycast	raycast;
	t_player	player;
	t_img		wall[4];
	t_img		game_img;
}	t_game;

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_read_scene
{
	int		fd;
	int		line_count;
	int		i;
	char	*line;
	char	*clean;
	char	*clean2;
}	t_read_scene;

//________________________________________________________________
//|______________________[FUNCTION PROTOTYPES]____________________|
//|_______________________________________________________________|

void	move_front_right(t_game *game, double x, double y);
void	move_back_left(t_game *game, double x, double y);
void	rotate(t_game *game, double angle);
void	movement(t_game *game);
void	get_player_angle(t_game *game, int x, int y);
void	raycast(t_game *game);
int		get_color(t_game *game, int x, int y, int i);

bool	render_background(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);

// VALIDATION
bool	ft_validate_args(int ac, char **av);

// INITIATE STRUCTS
t_game	*ft_init_game(char *map_path);
t_game	*ft_create_game(void);
void	ft_init_mlx(t_game *game);
t_scene	*ft_create_scene(char *path);
void	ft_load_textures(t_game *game);

// PARSING
void	check_scene(char *path, t_scene *scene);
void	read_scene(char *path, t_scene *scene);
void	check_for_empty(t_scene *scene);
void	separate_map(t_scene *scene);
void	validate_elements(t_scene *scene);
void	validate_map_characters(char **map);
void	validate_map(t_scene *scene);

//----------read_scene-----------//
int		ft_count_lines(char *path);
char	*spaces_for_tabs(char *line);
int		has_tabs(const char *line);
void	change_tabs(const char *line, char *new_line);
//----------separate_map---------//
int		get_map_start_index(char **lines);
int		count_map_lines(char **lines);
void	copy_map_lines(t_scene *scene, int start, int count);
int		ft_get_max_line_length(char **map);
bool	ft_is_map_line(char *line);
//----------validate_elements---------//
void	parse_textures(t_scene *scene, char *line);
void	parse_no(t_scene *scene, char *line);
void	parse_so(t_scene *scene, char *line);
void	parse_we(t_scene *scene, char *line);
void	parse_ea(t_scene *scene, char *line);
void	parse_colors(t_scene *scene, char *line);
int		parse_rgb(const char *line);
char	*trim_and_check_digit(char *str);
void	free_rgb_parts(char **arr, char **trimmed);
bool	ft_isdigit_str(char *str);
//----------validate_map_chars-------//
bool	is_valid_map_char(char c);
//----------validate_map-------------//
void	pad_map(t_scene *scene);
void	find_player(t_scene *scene);
void	set_spawn(t_scene *scene, int x, int y, char dir);
void	check_closed_map(t_scene *scene);
char	**duplicate_map(t_scene *scene);
void	flood_fill(char **map, t_coords *max_coords, int x, int y);

// ERROR
void	ft_end(int nbr, t_game *g);
void	free_all(t_game *g);
void	free_scene(t_scene *scene);
void	free_array(char **arr, int max);
int		ft_exit(t_game *g);

// FREE UTILS
//  void	free_array(char **arr);

bool	init_game_data(t_game *game);
bool	get_walls(t_game *game);
void	init_player(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	movement(t_game *game);
int		draw_loop(t_game *game);
void	dda(t_game *game);
void	calculate_distance(t_game *game);

#endif