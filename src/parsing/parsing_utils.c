/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:43:01 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/14 15:34:04 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

///Save the map file content in a string
///@param acc The string to store the map file content
///@param line The line read from the map file
///@return 1 if the line is not empty, 0 otherwise
int	save_map(char **acc, char *line)
{
	if (!line || *line == '\0')
	{
		if (line)
			free(line);
		return (0);
	}
	*acc = ft_strrep(*acc, line);
	free(line);
	return (1);
}

///Check if the file extension is .cub
///@param file The file name
///@return 0 if the file extension is .cub, 1 otherwise
int	check_file_ext(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot)
		return (printf("Error\nNo file extension\n"), 1);
	if (ft_strcmp(dot, ".cub") != 0)
		return (printf("Error\nInvalid file extension\n"), 1);
	return (0);
}

///Check if the map is valid
///@param cub The cub struct
///@param y The y coordinate
///@param x The x coordinate
///@return 0 if the map is valid, 1 otherwise
int	ft_isvalid(char **map, int y, int x)
{
	if (ft_strchr("NWES01D2", map[y][x]) == NULL)
		return (1);
	if (ft_strchr("NWES01D2", map[y + 1][x]) == NULL)
		return (1);
	if (ft_strchr("NWES01D2", map[y - 1][x]) == NULL)
		return (1);
	if (ft_strchr("NWES01D2", map[y][x + 1]) == NULL)
		return (1);
	if (ft_strchr("NWES01D2", map[y][x - 1]) == NULL)
		return (1);
	return (0);
}

/// Check if map is closed by walls
/// @param map The map as a double array
/// @param i The line index
/// @param j The column index
/// @param cub The cub struct
/// @return 1 if the map is not closed, 0 otherwise
int	check_map_walls(char **map, int y, int x, t_cub *cub)
{
	check_valid_line(map, y, 0, cub);
	check_valid_line(map, y, line_lenght(map[y]), cub);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' '
		|| map[y][x + 1] == ' ' || ft_isvalid(map, y, x) == 1)
		return (1);
	return (0);
}
