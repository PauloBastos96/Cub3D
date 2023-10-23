/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:12 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/23 16:53:57 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "string.h"
#include <fcntl.h>

typedef struct s_rgb
{
	int r;
	int g;
	int b;
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

typedef struct s_cub
{
	char	**file;
	char	**map;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	*sprite;
	int		height;
	int		width;
	t_rgb	*floor_color;
	t_rgb	*ceiling_color;
}			t_cub;

int			check_file_ext(char *file);
void		read_map(t_cub *cub, char *file);
void		throw_err(char *err);
int			save_map(char **acc, char *line);
int			ft_isvalid(char **map, int y, int x);
void		check_valid(t_cub *cub);
void		define_line_limiter(t_cub *cub);
void		check_valid_line(char **map, int y, int x, char c);
int			line_lenght(char *line);
char		**set_map_even(t_cub *cub);