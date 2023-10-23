/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:43:01 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/23 12:40:26 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

///Print error message and exit game
///@param err The error message
void	throw_err(char *err)
{
	printf("Error\n%s\n", err);
	exit(0);
}

///Save the map file content in a string
///@param acc The string to store the map file content
///@param line The line read from the map file
///@return 1 if the line is not empty, 0 otherwise
int	save_map(char **acc, char *line)
{
	char	*new;

	if (!line || *line == '\0')
	{
		if (line)
			free(line);
		return (0);
	}
	new = ft_strjoin(*acc, line);
	free(*acc);
	*acc = new;
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
int	ft_isvalid(t_cub *cub, int y, int x)
{
	if (ft_strchr("NWES01", cub->map[y][x]) == NULL)
		return (1);
	if (ft_strchr("NWES01", cub->map[y + 1][x]) == NULL)
		return (1);
	if (ft_strchr("NWES01", cub->map[y - 1][x]) == NULL)
		return (1);
	if (ft_strchr("NWES01", cub->map[y][x + 1]) == NULL)
		return (1);
	if (ft_strchr("NWES01", cub->map[y][x - 1]) == NULL)
		return (1);
	return (0);
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
