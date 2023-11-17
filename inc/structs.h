/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:47:46 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 15:49:14 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
	long int		hex;
}					t_rgb;

typedef struct s_vector
{
	float	x;
	float	y;
}			t_vector;

typedef struct s_ray
{
	float		angle;
	float		distance;
	int			x_pos;
	bool		is_vert;
}			t_ray;

typedef struct s_player
{
	t_vector	*position;
	t_vector	*direction;
	float		angle;
}			t_player;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_len;
}			t_image;

typedef struct s_textures
{
	int		anim_frame;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	char	*barrel_path;
	char	*door_path;
	char	**anim_wall_paths;
	t_image	*north;
	t_image	*south;
	t_image	*west;
	t_image	*east;
	t_image	*barrel_prop;
	t_image	*door;
	t_image	*animated_walls[4];
}			t_textures;

typedef struct s_cub
{
	char		**file;
	char		**map;
	char		*sprite;
	int			prop_y;
	int			prop_x;
	int			height;
	int			width;
	int			turning;
	int			debug_line;
	void		*mlx;
	void		*win;
	bool		show_fps;
	bool		show_minimap;
	bool		show_fog;
	bool		show_debug_line;
	t_rgb		*floor_color;
	t_rgb		*ceiling_color;
	t_image		*frame_buffer;
	t_image		*minimap;
	t_player	*player;
	t_textures	*textures;
}			t_cub;

#endif
