/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:03:51 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 16:06:40 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "structs.h"
# include <stdbool.h>

void	raycast_in_fov(t_cub *cub);
void	init_horizontal_values(t_cub *cub, t_vector *vector, 
			float *y_offset, float angle);
void	init_vertical_values(t_cub *cub, t_vector *vector, 
			float *x_offset, float angle);
void	distance_checks(t_cub *cub, t_ray *ray, t_vector coords, bool vert);
float	get_distance(t_vector player, t_vector wall);
bool	is_wall(t_cub *cub, int x, int y);

#endif
