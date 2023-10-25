/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:14:02 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/25 16:30:41 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	render_frame(t_cub *cub)
{
	int		fps;
	char	*fps_s;

	if (clock() - cub->last_frame < 16)
		return (0);
	fps = 1000 / (clock() - cub->last_frame);
	fps_s = ft_itoa(fps);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame_buffer->img, 0, 0);
	mlx_string_put(cub->mlx, cub->win, 10, 10, 0xffffff, fps_s);
	cub->last_frame = clock();
	free(fps_s);
	return (0);
}

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
	//movement_handler(keycode, cub);
	return (0);
}

///Register hooks for the window (close window and key presses)
/// @param cub The cub struct
void	register_hooks(t_cub *cub)
{
	mlx_key_hook(cub->win, key_hook, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_window_event, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
}

void	mlx_setup(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	cub->frame_buffer = ft_calloc(sizeof(t_image), 1);
	cub->frame_buffer->img = mlx_new_image(cub->mlx, 
			WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->frame_buffer->addr = mlx_get_data_addr(cub->frame_buffer->img,
			&(cub->frame_buffer->bpp),
			&(cub->frame_buffer->line_len),
			&(cub->frame_buffer->endian));
	cub->frame_buffer->w = WINDOW_WIDTH;
	cub->frame_buffer->h = WINDOW_HEIGHT;
}
