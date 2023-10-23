/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/23 22:21:17 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Set textures from the map file
/// @param cub The cub struct
void	check_textures(t_cub *cub)
{
	if (!cub->north_texture || !cub->south_texture || !cub->west_texture
		|| !cub->east_texture || !cub->floor_color
		|| !cub->ceiling_color)
		throw_err("Invalid file", cub);
	if (open(cub->north_texture, O_RDONLY) == -1
		|| open(cub->south_texture, O_RDONLY) == -1
		|| open(cub->west_texture, O_RDONLY) == -1
		|| open(cub->east_texture, O_RDONLY) == -1)
		throw_err("Invalid texture", cub);
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

/// Store textures and colors in the cub struct
/// @param cub The cub struct
/// @param acc The map file content
void	store_info(t_cub *cub, char *acc)
{
	int	i;

	i = 0;
	cub->file = ft_split(acc, '\n');
	free(acc);
	while (cub->file[i])
	{
		if (ft_strncmp(cub->file[i], "NO", 2) == 0)
			cub->north_texture = ft_strchr(cub->file[i], '.');
		if (ft_strncmp(cub->file[i], "SO", 2) == 0)
			cub->south_texture = ft_strchr(cub->file[i], '.');
		if (ft_strncmp(cub->file[i], "WE", 2) == 0)
			cub->west_texture = ft_strchr(cub->file[i], '.');
		if (ft_strncmp(cub->file[i], "EA", 2) == 0)
			cub->east_texture = ft_strchr(cub->file[i], '.');
		if (ft_strncmp(cub->file[i], "F ", 2) == 0)
			cub->floor_color = get_color(cub->file[i]);
		if (ft_strncmp(cub->file[i], "C ", 2) == 0)
			cub->ceiling_color = get_color(cub->file[i]);
		i++;
	}
	if (!cub->floor_color || !cub->ceiling_color)
		throw_err("Invalid color", cub);
	check_textures(cub);
}

///Store map in the cub struct
///@param cub The cub struct
///@param acc The map file content
///@return 0 if the map was stored, 1 otherwise
int	store_map(t_cub *cub)
{
	int	i;
	int	j;

	j = 5;
	i = 0;
	define_line_limiter(cub);
	while (cub->file[++j])
		i++;
	cub->height = i;
	cub->map = ft_calloc(cub->height + 1, sizeof(char *));
	i = 0;
	j = 5;
	while (cub->file[++j])
	{
		cub->map[i] = ft_strdup(cub->file[j]);
		i++;
	}
	if (check_valid(cub))
		return (1);
	return (0);
}

///Read the map file
///@param cub The cub struct
///@param file The map file
void	read_map(t_cub *cub, char *file)
{
	int		fd;
	char	*acc;
	char	*line;

	acc = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		throw_err("Invalid file", cub);
	while (1)
	{
		line = get_next_line(fd);
		if (!save_map(&acc, line))
			break ;
	}
	close(fd);
	store_info(cub, acc);
	if (store_map(cub))
		throw_err("Invalid map", cub);
}

/// Check if map is valid
/// @param cub The cub struct
/// @return 0 if the map is valid, 1 otherwise
int	check_valid(t_cub *cub)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 5;
	map = set_map_even(cub);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("0NSWE", map[i][j]))
			{
				if (i == 0)
					check_valid_line(map, i, j, cub);
				else if (i == cub->height - 1)
					check_valid_line(map, i, j, cub);
				else
				{
					check_valid_line(map, i, 0, cub);
					check_valid_line(map, i, line_lenght(map[i]), cub);
					if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
						|| map[i][j - 1] == ' ' || map[i][j
						+ 1] == ' ' || ft_isvalid(map, i, j) == 1)
					{
						free_split(map);
						return (1);
					}
				}
			}
			j++;
		}
		i++;
	}
	free_split(map);
	return (0);
}
