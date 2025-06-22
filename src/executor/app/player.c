#include "cub3d.h"

int key_press(int keycode, t_game *game)
{
    if (keycode == XK_w)
    {
        printf("MOVING UP!!!");
        game->player.is_moving_up = true;
    }
    if (keycode == XK_a)
        game->player.is_moving_left = true;
    if (keycode == XK_d)
        game->player.is_moving_right = true;
    if (keycode == XK_s)
        game->player.is_moving_down = true;
    if (keycode == XK_Left)
        game->player.left_rotate = true;
    if (keycode == XK_Right)
        game->player.right_rotate = true;
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == XK_w)
    {
        printf("RELEASING MOVING UP!!!");
        game->player.is_moving_up = false;
    }
    if (keycode == XK_a)
        game->player.is_moving_left = false;
    if (keycode == XK_d)
        game->player.is_moving_right = false;
    if (keycode == XK_s)
        game->player.is_moving_down = false;
    if (keycode == XK_Left)
        game->player.left_rotate = false;
    if (keycode == XK_Right)
        game->player.right_rotate = false;
    return (0);
}

void movement(t_game *game)
{
    int move_speed = 5;
    int angle_speed = 0.1;
    int cos_angle = cos(game->player.angle);
    int sin_angle = sin(game->player.angle);

    if (game->player.left_rotate)
        game->player.angle -= angle_speed;
    if (game->player.right_rotate)
        game->player.angle += angle_speed;
    if (game->player.angle > 2 * PI)
        game->player.angle = 0;
    if (game->player.angle < 0)
        game->player.angle = 2 * PI;

    if (game->player.is_moving_up)
    {
        game->player.x += cos_angle * move_speed;
        game->player.y += sin_angle * move_speed;
    }
    else if (game->player.is_moving_down)
    {
        game->player.x -= cos_angle * move_speed;
        game->player.y -= sin_angle * move_speed;
    }
    else if (game->player.is_moving_left)
    {
        game->player.x += cos_angle * move_speed;
        game->player.y -= sin_angle * move_speed;
    }
    else if (game->player.is_moving_right)
    {
        game->player.x -= cos_angle * move_speed;
        game->player.y += sin_angle * move_speed;
    }
}
