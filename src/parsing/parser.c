/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:40:20 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/17 15:52:00 by ffilipe-         ###   ########.fr       */
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
    cub->map = ft_split(acc, '\n');
}