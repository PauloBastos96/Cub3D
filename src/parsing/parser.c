/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/23 15:13:42 by paulorod         ###   ########.fr       */
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

///Store map info in the cub struct
///@param cub The cub struct
///@param acc The map file content
void	store_info(t_cub *cub, char *acc)
{
	int	i;
	int	j;

	j = 5;
	i = 0;
	cub->file = ft_split(acc, '\n');
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
	store_info(cub, acc);
	free(acc);
}

/// Check if the line is valid
/// @param cub The cub struct
/// @param y The y coordinate
/// @param x The x coordinate
/// @param c The character to check
void	check_valid_line(char **map, int y, int x, char c)
{
	if (map[y][x] == c)
		return ;
	while (map[y][x])
	{
		if (map[y][x] == ' ')
			x++;
		else
			break ;
	}
	if (map[y][x] == c)
		return ;
	else
		throw_err("Invalid map");
}

///Fill the map **char with the map content, filling empty spaces with spaces
///@param cub The cub struct
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

///Check if the map is valid
///@param cub The cub struct
void	check_valid(t_cub *cub)
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
					check_valid_line(map, i, j, '1');
				else if (i == cub->height - 1)
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
	free_split(map);
}
