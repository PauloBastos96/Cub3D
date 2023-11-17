/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:08:25 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 15:43:41 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/// Get the minimum value between two numbers
/// @param a First number
/// @param b Second number
/// @return The lowest number between a and b
float	get_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

/// Clamp a number between a min and max value
/// @param n Number to clamp
/// @param min The minimum value
/// @param max The maximum value
/// @return The clamped number
float	clamp(float n, float min, float max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}

/// Convert degrees to radians
/// @param deg Angle in degrees
/// @return Angle in radians
float	deg_to_rad(float deg)
{
	return (deg * (PI / 180));
}

/// Convert radians to degrees
/// @param rad Angle in radians
/// @return Angle in degrees
float	rad_to_deg(float rad)
{
	return (rad * (180 / PI));
}

/// Get the distance between two points
/// @param player The player position
/// @param wall The wall position
/// @return The distance between the two points
float	get_distance(t_vector player, t_vector wall)
{
	return (sqrtf(powf(player.x - wall.x, 2) + powf(player.y - wall.y, 2)));
}
