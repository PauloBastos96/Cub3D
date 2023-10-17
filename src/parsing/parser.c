/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/17 20:04:42 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
    cub->file = ft_split(acc, '\n');
    check_valid(cub);
}

void check_valid(t_cub *cub)
{
    int i;
    int j;

    i = 0;
    j = 5;
    while(cub->file[++j])
        i++;
    cub->map = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    j = 5;
    while(cub->file[++j])
    {
        cub->map[i] = cub->file[j];
        i++;
    }
    cub->map[i] = NULL;
    i = 0;
    while(cub->map[i])
    {
        j = 1;
        while(cub->map[i][j])
        {
            if(ft_strchr("0NSWE", cub->map[i][j]))
            {
                if(cub->map[i - 1][j] == ' ' || cub->map[i + 1][j] == ' ' || cub->map[i][j - 1] == ' ' || cub->map[i][j + 1] == ' ')
                    throw_err(cub, "Invalid map");
            }
            j++;
        }
        i++;
    }
}


