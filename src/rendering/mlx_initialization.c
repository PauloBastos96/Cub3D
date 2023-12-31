/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:14:02 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 22:17:15 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

///Process window close event
/// @param cub The cub struct
int	close_window_event(t_cub *cub)
{
	exit_game(cub);
	return (0);
}

///Process key presses
/// @param keycode The key pressed
/// @param cub The cub struct
int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		exit_game(cub);
	if (keycode == XK_F3)
		cub->show_fps = !cub->show_fps;
	if (keycode == XK_F2)
		cub->show_minimap = !cub->show_minimap;
	if (keycode == XK_F1)
		cub->show_debug_line = !cub->show_debug_line;
	if (cub->show_debug_line)
	{
		if (keycode == XK_Up)
			cub->debug_line++;
		if (keycode == XK_Down)
			cub->debug_line--;
		if (keycode == XK_Tab)
			cub->debug_line += 10;
	}
	movement_handler(keycode, cub);
	return (0);
}

/// Process mouse movement
/// @param x The x coordinate of the mouse
/// @param y The y coordinate of the mouse (not used)
/// @param cub The cub struct
int	mouse_hook(int x, int y, t_cub *cub)
{
	if (x < WINDOW_WIDTH / 2)
		rotation_handler(-1, cub, MOUSE_ROTATION_SPEED);
	else if (x > WINDOW_WIDTH / 2)
		rotation_handler(1, cub, MOUSE_ROTATION_SPEED);
	mlx_mouse_move(cub->mlx, cub->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	(void)y;
	return (0);
}

///Register hooks for the window (close window and key presses)
/// @param cub The cub struct
void	register_hooks(t_cub *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_hook, cub);
	mlx_hook(cub->win, MotionNotify, PointerMotionMask,
		mouse_hook, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_window_event, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
}

/// Initialize the mlx window
/// @param cub The cub struct
void	mlx_setup(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	cub->frame_buffer = ft_calloc(sizeof(t_image), 1);
	if (!cub->frame_buffer)
		throw_err("Couldn't allocate memory", cub);
	cub->frame_buffer->img = mlx_new_image(cub->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->frame_buffer->addr = mlx_get_data_addr(cub->frame_buffer->img,
			&(cub->frame_buffer->bpp),
			&(cub->frame_buffer->line_len),
			&(cub->frame_buffer->endian));
	cub->frame_buffer->w = WINDOW_WIDTH;
	cub->frame_buffer->h = WINDOW_HEIGHT;
}
