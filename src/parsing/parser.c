/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/23 16:46:46 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void check_textures(t_cub *cub)
{
	if(!cub->north_texture || !cub->south_texture || !cub->west_texture
		|| !cub->east_texture || !cub->floor_color
		|| !cub->ceiling_color)
		throw_err("Invalid file");
	if(open(cub->north_texture, O_RDONLY) == -1
		|| open(cub->south_texture, O_RDONLY) == -1
		|| open(cub->west_texture, O_RDONLY) == -1
		|| open(cub->east_texture, O_RDONLY) == -1)
		throw_err("Invalid texture");
}

t_rgb *get_color(char *line)
{
	t_rgb *color;
	char **rgb;

	color = ft_calloc(1, sizeof(t_rgb));
	line = ft_strchr(line, ' ');
	rgb = ft_split(line, ',');
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (color);
}

void store_info(t_cub *cub, char *acc)
{
	int i;

	i = 0;
	cub->file = ft_split(acc, '\n');
	while(cub->file[i])
	{
		if(ft_strncmp(cub->file[i], "NO", 2) == 0)
			cub->north_texture = ft_strchr(cub->file[i], '.');
		if(ft_strncmp(cub->file[i], "SO", 2) == 0)
			cub->south_texture = ft_strchr(cub->file[i], '.');
		if(ft_strncmp(cub->file[i], "WE", 2) == 0)
			cub->west_texture = ft_strchr(cub->file[i], '.');
		if(ft_strncmp(cub->file[i], "EA", 2) == 0)
			cub->east_texture = ft_strchr(cub->file[i], '.');
		if(ft_strncmp(cub->file[i], "F ", 2) == 0)
			cub->floor_color = get_color(cub->file[i]);
		if(ft_strncmp(cub->file[i], "C ", 2) == 0)
			cub->ceiling_color = get_color(cub->file[i]);
		i++;
	}
	check_textures(cub);
}

void	store_map(t_cub *cub)
{
	int i;
	int j;

	j = 5;
	i = 0;
	define_line_limiter(cub);
	while (cub->file[++j])
		i++;
	cub->height = i;	
	cub->map = ft_calloc(cub->height + 1, sizeof(char *));
	i = 0;
	j = 5;
	while(cub->file[++j])
	{
		cub->map[i] = ft_calloc(cub->width + 1, sizeof(char*));
		cub->map[i] = cub->file[j];
		i++;
	}
	check_valid(cub);
}

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
	store_info(cub, acc);
	store_map(cub);
}

void	check_valid(t_cub *cub)
{
	int	i;
	int	j;
	char **map;
	
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
					check_valid_line(map, i, j, '1');
				else if(i == cub->height - 1)
					check_valid_line(map, i, j, '1');
				else
				{
                    check_valid_line(map, i, 0, '1');   
                    check_valid_line(map, i, line_lenght(map[i]), '1');  
                    if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
						|| map[i][j - 1] == ' ' || map[i][j
						+ 1] == ' ' || ft_isvalid(map, i, j) == 1)
						throw_err("Invalid map");
				}
			}
			j++;
		}
		i++;
	}
}
