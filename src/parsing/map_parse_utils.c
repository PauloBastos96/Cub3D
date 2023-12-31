/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:13:01 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/17 15:20:23 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/// Get map line size to set map width
/// @param cub The cub struct
void	define_line_limiter(t_cub *cub)
{
	int	j;

	cub->width = 0;
	j = 5;
	while (cub->file[++j])
	{
		if ((int)ft_strlen(cub->file[j]) > cub->width)
			cub->width = ft_strlen(cub->file[j]);
	}
}

/// Check if the line is valid
/// @param cub The cub struct
/// @param y The y coordinate
/// @param x The x coordinate
/// @param cub The cub struct
void	check_valid_line(char **map, int y, int x, t_cub *cub)
{
	if (map[y][x] == '1')
		return ;
	while (map[y][x])
	{
		if (map[y][x] == ' ')
			x++;
		else
			break ;
	}
	if (map[y][x] == '1')
		return ;
	else
	{
		free_split(map);
		throw_err("Invalid map", cub);
	}
}

/// Fill map with data and spaces on empty spaces
/// @param cub The cub struct
/// @return The map in a double array
char	**set_map_even(t_cub *cub)
{
	int		i;
	int		j;
	int		counter;
	char	**map;

	i = -1;
	j = 5;
	counter = 0;
	map = ft_calloc(cub->height + 1, sizeof(char *));
	if (!map)
		throw_err("Couldn't allocate memory", cub);
	define_line_limiter(cub);
	while (cub->file[++j])
	{
		check_player(cub->file[j], &counter);
		map[++i] = ft_calloc(cub->width + 1, sizeof(char *));
		if (!map[i])
			throw_err("Couldn't allocate memory", cub);
		ft_memset(map[i], ' ', cub->width);
		ft_memcpy(map[i], cub->file[j], ft_strlen(cub->file[j]));
	}
	check_player_count(counter, map, cub);
	return (map);
}

/// Get the line lenght, not counting spaces
/// @param line The line to check
/// @return The line lenght
int	line_lenght(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	while (line[i] != '1' && i > 0)
		i--;
	return (i);
}

/// Set colors from the map file
/// @param line The color line
/// @return The color in a t_rgb struct
t_rgb	*get_color(char *line)
{
	t_rgb	*color;
	char	**rgb;

	color = ft_calloc(1, sizeof(t_rgb));
	if (!color)
		return (NULL);
	line = ft_strchr(line, ' ');
	rgb = ft_split(line, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (free_split(rgb), free(color), NULL);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (free(color), NULL);
	return (color);
}
