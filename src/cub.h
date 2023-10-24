/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:12 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/23 22:02:47 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "string.h"
# include <fcntl.h>

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
int			save_map(char **acc, char *line);
int			ft_isvalid(char **map, int y, int x);
int			line_lenght(char *line);
void		read_map(t_cub *cub, char *file);
void		throw_err(char *err, t_cub *cub);
int			check_valid(t_cub *cub);
void		free_split(char **split);
void		free_map(t_cub *cub);
void		define_line_limiter(t_cub *cub);
void		check_valid_line(char **map, int y, int x, t_cub *cub);
void		free_colors(t_cub *cub);
void		exit_game(t_cub *cub);
char		**set_map_even(t_cub *cub);

#endif