/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:12 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/17 19:51:56 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "string.h"
#include <fcntl.h>

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
	int		floor_color[3];
	int		ceiling_color[3];
}			t_cub;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

int			check_file_ext(char *file);
void		read_map(t_cub *cub, char *file);
void		throw_err(t_cub *cub, char *err);
int			save_map(char **acc, char *line);
int			ft_isspace(char c);
void		check_valid(t_cub *cub);