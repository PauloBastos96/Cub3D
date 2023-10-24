/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:13:01 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/23 21:57:24 by paulorod         ###   ########.fr       */
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
	char	**map;

	i = 0;
	j = 5;
	map = ft_calloc(cub->height + 1, sizeof(char *));
	i = 0;
	j = 5;
	cub->width = 0;
	define_line_limiter(cub);
	while (cub->file[++j])
	{
		map[i] = ft_calloc(cub->width + 1, sizeof(char *));
		ft_memset(map[i], ' ', cub->width);
		ft_memcpy(map[i], cub->file[j], ft_strlen(cub->file[j]));
		i++;
	}
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