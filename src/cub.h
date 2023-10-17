/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:12 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/17 15:25:17 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "string.h"
#include <fcntl.h>

typedef struct  s_cub
{
    char        **map;
    int         res_x;
    int         res_y;
    char        *north;
    char        *south;
    char        *west;
    char        *east;
    char        *sprite;
    int         floor;
    int         ceiling;
}   t_cub;

typedef struct  s_mlx
{
    void        *mlx;
    void        *win;
}   t_mlx;

int check_file_ext(char *file);
void read_map(t_cub *cub, char *file);
void throw_err(t_cub *cub, char *err);
int	save_map(char **acc, char *line);