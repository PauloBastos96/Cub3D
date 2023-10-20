/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/20 16:11:42 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

///Store map info in the cub struct
///@param cub The cub struct
///@param acc The map file content
void	store_info(t_cub *cub, char *acc)
{
	char	**colors;

	cub->file = ft_split(acc, '\n');
	cub->north_texture = ft_strchr(cub->file[0], '/');
	cub->south_texture = ft_strchr(cub->file[1], '/');
	cub->west_texture = ft_strchr(cub->file[2], '/');
	cub->east_texture = ft_strchr(cub->file[3], '/');
	colors = ft_split(cub->file[4], ',');
	cub->floor_color.r = ft_atoi(colors[0]);
	cub->floor_color.g = ft_atoi(colors[1]);
	cub->floor_color.b = ft_atoi(colors[2]);
	free_split(colors);
	colors = ft_split(cub->file[5], ',');
	cub->ceiling_color.r = ft_atoi(colors[0]);
	cub->ceiling_color.g = ft_atoi(colors[1]);
	cub->ceiling_color.b = ft_atoi(colors[2]);
	free_split(colors);
	check_valid(cub);
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
		throw_err("Invalid file");
	while (1)
	{
		line = get_next_line(fd);
		if (!save_map(&acc, line))
			break ;
	}
	close(fd);
	while (1) //?is this supposed to be repeated?
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			free(line);
	}
	store_info(cub, acc);
	free(acc);
}

/// Check if the line is valid
/// @param cub The cub struct
/// @param y The y coordinate
/// @param x The x coordinate
/// @param c The character to check
void	check_valid_line(t_cub *cub, int y, int x, char c)
{
	if (cub->map[y][x] == c)
		return ;
	while (cub->map[y][x])
	{
		if (cub->map[y][x] == ' ')
			x++;
		else
			break ;
	}
	if (cub->map[y][x] == c)
		return ;
	else
		throw_err("Invalid map");
}

///Fill the map **char with the map content, filling empty spaces with spaces
///@param cub The cub struct
char	**set_map_even(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 5;
	while (cub->file[++j])
		i++;
	cub->map = ft_calloc(i + 1, sizeof(char *));
	cub->height = i;
	i = 0;
	j = 5;
	cub->width = 0;
	while (cub->file[++j])
	{
		if ((int)ft_strlen(cub->file[j]) > cub->width)
			cub->width = ft_strlen(cub->file[j]);
	}
	j = 5;
	while (cub->file[++j])
	{
		cub->map[i] = ft_calloc(cub->width + 1, sizeof(char*));
		ft_memset(cub->map[i], ' ', cub->width);
		ft_memcpy(cub->map[i], cub->file[j], ft_strlen(cub->file[j]));
		i++;
	}
	return (cub->map);
}

///Check if the map is valid
///@param cub The cub struct
void	check_valid(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 5;
	cub->map = set_map_even(cub);
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (ft_strchr("0NSWE", cub->map[i][j]))
			{
				if (i == 0)
					check_valid_line(cub, i, j, '1');
				else if (i == cub->height - 1)
					check_valid_line(cub, i, j, '1');
				else
				{
					check_valid_line(cub, i, 0, '1');
					check_valid_line(cub, i, line_lenght(cub->map[i]), '1');
					if (cub->map[i - 1][j] == ' ' || cub->map[i + 1][j] == ' '
						|| cub->map[i][j - 1] == ' ' || cub->map[i][j
						+ 1] == ' ' || ft_isvalid(cub, i, j) == 1)
						throw_err("Invalid map");
				}
			}
			j++;
		}
		i++;
	}
}
