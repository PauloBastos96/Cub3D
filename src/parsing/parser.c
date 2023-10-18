/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/18 16:22:09 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void store_info(t_cub *cub, char *acc)
{
    char **colors;
    
    cub->file = ft_split(acc, '\n');
    cub->north_texture = ft_strchr(cub->file[0], '.');
    cub->south_texture = ft_strchr(cub->file[1], '.');
    cub->west_texture =  ft_strchr(cub->file[2], '.');
    cub->east_texture = ft_strchr(cub->file[3], '.');
    colors = ft_split(cub->file[4], ',');
    cub->floor_color.r = ft_atoi(colors[0]);
    cub->floor_color.g = ft_atoi(colors[1]);
    cub->floor_color.b = ft_atoi(colors[2]);
    colors = ft_split(cub->file[5], ',');
    cub->ceiling_color.r = ft_atoi(colors[0]);
    cub->ceiling_color.g = ft_atoi(colors[1]);
    cub->ceiling_color.b = ft_atoi(colors[2]);
    free(colors);
    printf("north_texture: %s\n", cub->north_texture);
    printf("south_texture: %s\n", cub->south_texture);
    printf("west_texture: %s\n", cub->west_texture);
    printf("east_texture: %s\n", cub->east_texture);
    printf("floor_color: %d, %d, %d\n", cub->floor_color.r, cub->floor_color.g, cub->floor_color.b);
    printf("ceiling_color: %d, %d, %d\n", cub->ceiling_color.r, cub->ceiling_color.g, cub->ceiling_color.b);
    check_valid(cub);
}

void read_map(t_cub *cub, char *file)
{
    int fd;
    char *acc;
    char *line;

    acc = NULL;
    fd = open(file, O_RDONLY);
    if(fd == -1)
        throw_err(cub, "Invalid file");
    while(1)
    {
        line = get_next_line(fd);
        if(!save_map(&acc, line))
            break;
    }
    close(fd);
    while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			free(line);
	}
    store_info(cub, acc);
}

void check_valid(t_cub *cub)
{
    int i;
    int j;

    i = 0;
    j = 5;
    while(cub->file[++j])
        i++;
    cub->map = ft_calloc(i + 1, sizeof(char *));
    cub->height = i;
    i = 0;
    j = 5;
    cub->width = 0;
    while(cub->file[++j])
    {
        if((int)ft_strlen(cub->file[j]) > cub->width)
            cub->width = ft_strlen(cub->file[j]);
    }
    j = 5;
    while(cub->file[++j])
    {
        cub->map[i] = malloc(cub->width + 1);
        ft_memset(cub->map[i], ' ', cub->width);
        ft_memcpy(cub->map[i], cub->file[j], ft_strlen(cub->file[j]));
        printf("map[i] = %s\n", cub->map[i]);
        i++;
    }
    i = 0;
    while(cub->map[i])
    {
        j = 0;
        while(cub->map[i][j])
        {
            if(ft_strchr("0NSWE", cub->map[i][j]))
            {
                if(i == 0)
                {
                    printf("here\n");
                }
                else
                {
                    printf("y: %d, x: %d, c : %c\n", i, j, cub->map[i][j + 1]);
                    if(cub->map[i - 1][j] == ' ' || cub->map[i + 1][j] == ' ' || cub->map[i][j - 1] == ' ' || cub->map[i][j + 1] == ' ' || ft_isvalid(cub,i,j) == 1)
                        throw_err(cub, "Invalid map");
                }
            }
            j++;
        }
        i++;
    }
}


