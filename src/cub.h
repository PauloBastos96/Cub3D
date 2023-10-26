/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:12 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/26 13:50:19 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "string.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <X11/Xutil.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define KEY_ESC 65307
# define MAX_FPS 60

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
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

typedef struct s_cub
{
	char		**file;
	char		**map;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite;
	int			height;
	int			width;
	void		*mlx;
	void		*win;
	bool		show_fps;
	t_rgb		*floor_color;
	t_rgb		*ceiling_color;
	t_player	*player;
	t_image		*frame_buffer;
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
char		**set_map_even(t_cub *cub);
t_rgb		*get_color(char *line);
uint64_t	gettimeofday_ms(void);
uint64_t	delta_time(void);

#endif
