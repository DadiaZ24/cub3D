#include "cub3d.h"

void draw_walls(t_game *game)
{
    char **map = game->scene->map;
    int color = 0x0000FF;
    int y;
    int x;

    y = -1;
    while (map[++y])
    {
        x = -1;
        while (map[y][++x])
        {
            if (map[y][x] == '1')
                draw_square(x * 64, y * 64, 64, color, game);
        }
    }
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
    int i;

    i = -1;
    while (++i < size)
    {
        put_pixel(game, x + i, y, color);
        put_pixel(game, x, y + i, color);
        put_pixel(game, x + size, y, color);
        put_pixel(game, x, y + size, color);
    }
}

int draw_loop(t_game *game)
{
    movement(game);
    draw_walls(game);
    printf("player x = %f\n player y = %f\n", game->player.x, game->player.y);
    draw_square(game->player.x, game->player.y, 10, 0x00FF00, game);
    mlx_put_image_to_window(game->mlx, game->window, game->game_img.mlx_img, 0, 0);
    return (0);
}
