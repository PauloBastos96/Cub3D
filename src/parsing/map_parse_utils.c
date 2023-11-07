/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:13:01 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/07 11:58:48 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

	i = 0;
	j = 5;
	counter = 0;
	cub->width = 0;
	map = ft_calloc(cub->height + 1, sizeof(char *));
	define_line_limiter(cub);
	while (cub->file[++j])
	{
		check_player(cub->file[j], &counter);
		map[i] = ft_calloc(cub->width + 1, sizeof(char *));
		ft_memset(map[i], ' ', cub->width);
		ft_memcpy(map[i], cub->file[j], ft_strlen(cub->file[j]));
		i++;
	}
	if (counter != 1)
		throw_err("Invalid amount of players", cub);
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

char *to_hex(int n)
{
	char *hex;
	char *hex_chars;
	int i;

	hex_chars = "0123456789ABCDEF";
	hex = ft_calloc(1, sizeof(char));
	i = 0;
	while (n > 0)
	{
		hex[i] = hex_chars[n % 16];
		n /= 16;
		i++;
	}
	return (hex);
}

/// Set colors from the map file
/// @param line The color line
/// @return The color in a t_rgb struct
t_rgb	*get_color(char *line)
{
	t_rgb	*color;
	char	**rgb;

	color = ft_calloc(1, sizeof(t_rgb));
	line = ft_strchr(line, ' ');
	rgb = ft_split(line, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (free_split(rgb), free(color), NULL);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_split(rgb);
	return (color);
}
