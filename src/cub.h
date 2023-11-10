/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:12 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/10 17:09:28 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB_H
# define CUB_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
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
# define ROTATION_SPEED 0.05f
# define WALL_DISTANCE 0.1f
# define PI 3.14159265359
# define FOV 60
# define MAP_SCALE 128
# define MINIMAP_SCALE 10

enum				e_direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
	long int		hex;
}					t_rgb;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

typedef struct s_vector
{
	float	x;
	float	y;
}			t_vector;

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
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	t_image	*north;
	t_image	*south;
	t_image	*west;
	t_image	*east;
}			t_textures;

typedef struct s_cub
{
	char		**file;
	char		**map;
	t_textures	*textures;
	char		*sprite;
	int			height;
	int			width;
	int			turning;
	int			debug_line;
	void		*mlx;
	void		*win;
	bool		show_fps;
	bool		show_minimap;
	t_rgb		*floor_color;
	t_rgb		*ceiling_color;
	t_player	*player;
	t_image		*frame_buffer;
	t_image		*minimap;
}			t_cub;

int			check_file_ext(char *file);
int			save_map(char **acc, char *line);
int			ft_isvalid(char **map, int y, int x);
int			line_lenght(char *line);
int			check_map_walls(char **map, int i, int j, t_cub *cub);
int			check_valid(t_cub *cub);
int			close_window_event(t_cub *cub);
int			key_hook(int keycode, t_cub *cub);
int			render_frame(t_cub *cub);
int			rgb_to_int(t_rgb *rgb);
void		register_hooks(t_cub *cub);
void		mlx_setup(t_cub *cub);
void		read_map(t_cub *cub, char *file);
void		throw_err(char *err, t_cub *cub);
void		free_split(char **split);
void		free_map(t_cub *cub);
void		define_line_limiter(t_cub *cub);
void		check_valid_line(char **map, int y, int x, t_cub *cub);
void		free_colors(t_cub *cub);
void		exit_game(t_cub *cub);
void		set_player_direction(t_player *player, char dir);
void		check_player(char *line, int *counter);
void		set_player_pos_and_dir(t_cub *cub, int i, int j);
void		movement_handler(int keycode, t_cub *cub);
void		rotation_handler(int direction, t_cub *cub);
void		cpy_img_to_frame_buffer(t_image *dst, t_image src, int x, int y);
void		set_pixel_color(t_image *img, int x, int y, int color);
void		display_map(t_cub *cub);
void		raycast_in_fov(t_cub *cub);
void		draw_walls(t_cub *cub, float dist, float angle, int i, int color);
void		draw_ray_from_player(t_cub *cub, float x, float y, float angle);
char		**set_map_even(t_cub *cub);
t_rgb		*get_color(char *line);
t_image		*create_new_image(void *mlx, int width, int height);
uint64_t	gettimeofday_ms(void);
uint64_t	delta_time(void);
uint32_t	get_pixel_color(t_image img, int x, int y);
float		get_next_player_x_pos(t_cub *cub, enum e_direction direction);
float		get_next_player_y_pos(t_cub *cub, enum e_direction direction);
float		deg_to_rad(float deg);
float		rad_to_deg(float rad);
float		clamp(float n, float min, float max);
float		get_min(float a, float b);
float		get_distance(t_vector player, t_vector wall);
bool		is_wall(t_cub *cub, int x, int y);

#endif
