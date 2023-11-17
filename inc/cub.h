/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:12 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/16 16:06:11 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "structs.h"
# include "math_utils.h"
# include "parsing.h"
# include "rendering.h"
# include "cleaners.h"
# include "raycasting.h"
# include "string.h"
# include <X11/Xutil.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <time.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define KEY_ESC 65307
# define MAX_FPS 60
# define PLAYER_SPEED 0.1f
# define ROTATION_SPEED 0.1f
# define MOUSE_ROTATION_SPEED 0.02f
# define WALL_DISTANCE 0.1f
# define PI 3.14159265359
# define FOV 60
# define MAP_SCALE 32
# define MAP_SCALE_F 32.0f
# define MINIMAP_SCALE 10
# define DOOR_TEXTURE "./src/textures/door.xpm"
# define ANIM_WALLS "./src/textures/TECHWALLB_1.xpm \
./src/textures/TECHWALLB_2.xpm ./src/textures/TECHWALLB_3.xpm \
./src/textures/TECHWALLB_4.xpm"

enum				e_direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

int			close_window_event(t_cub *cub);
int			key_hook(int keycode, t_cub *cub);
void		register_hooks(t_cub *cub);
void		mlx_setup(t_cub *cub);
void		movement_handler(int keycode, t_cub *cub);
void		rotation_handler(int direction, t_cub *cub, float speed);
float		get_next_player_x_pos(t_cub *cub, enum e_direction direction);
float		get_next_player_y_pos(t_cub *cub, enum e_direction direction);
uint64_t	gettimeofday_ms(void);
uint64_t	delta_time(void);

#endif
