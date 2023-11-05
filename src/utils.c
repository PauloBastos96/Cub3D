/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:26:32 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/05 23:16:51 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

///Print error message and exit game
///@param err The error message
void	throw_err(char *err, t_cub *cub)
{
	printf("%s[ERROR]\n%s%s\n", RED, err, RESET);
	if (cub)
		exit_game(cub);
	exit(1);
}

/// Create a new t_image
/// @param mlx The mlx pointer
/// @param width The image width
/// @param height The image height
/// @return A pointer to the new t_image
t_image	*create_new_image(void *mlx, int width, int height)
{
	t_image	*new_image;

	new_image = ft_calloc(1, sizeof(t_image));
	new_image->img = mlx_new_image(mlx, width, height);
	new_image->addr = mlx_get_data_addr(new_image->img,
			&(new_image->bpp),
			&(new_image->line_len),
			&(new_image->endian));
	new_image->w = width;
	new_image->h = height;
	return (new_image);
}

unsigned long int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/// Convert degrees to radians
/// @param deg Angle in degrees
/// @return Angle in radians
float	deg_to_rad(float deg)
{
	return (deg * (PI / 180));
}
