/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:44:37 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 15:52:09 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "structs.h"

int		rgb_to_int(t_rgb *rgb);
t_rgb	int_to_rgb(int color);
float	deg_to_rad(float deg);
float	rad_to_deg(float rad);
float	clamp(float n, float min, float max);
float	get_min(float a, float b);

#endif
