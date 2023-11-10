/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/11/10 17:09:36 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/// Set textures from the map file
/// @param cub The cub struct
void	check_textures(t_cub *cub)
{
	if (!cub->textures->north_path || !cub->textures->south_path
		|| !cub->textures->west_path || !cub->textures->east_path
		|| !cub->floor_color || !cub->ceiling_color)
		throw_err("Invalid file", cub);
	if (open(cub->textures->north_path, O_RDONLY) == -1
		|| open(cub->textures->south_path, O_RDONLY) == -1
		|| open(cub->textures->east_path, O_RDONLY) == -1
		|| open(cub->textures->west_path, O_RDONLY) == -1)
		throw_err("Invalid texture", cub);
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
			cub->textures->north_path = ft_strchr(cub->file[i], '.');
		if (ft_strncmp(cub->file[i], "SO", 2) == 0)
			cub->textures->south_path = ft_strchr(cub->file[i], '.');
		if (ft_strncmp(cub->file[i], "WE", 2) == 0)
			cub->textures->west_path = ft_strchr(cub->file[i], '.');
		if (ft_strncmp(cub->file[i], "EA", 2) == 0)
			cub->textures->east_path = ft_strchr(cub->file[i], '.');
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

	i = -1;
	j = 5;
	map = set_map_even(cub);
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("0NSWE", map[i][j]))
			{
				if (i == 0 || i == cub->height - 1)
					check_valid_line(map, i, j, cub);
				if (ft_strchr("NSWE", map[i][j]))
					set_player_pos_and_dir(cub, i, j);
				else if (check_map_walls(map, i, j, cub))
					return (free_split(map), 1);
			}
			j++;
		}
	}
	return (free_split(map), 0);
}
