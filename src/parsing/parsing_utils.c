/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:43:01 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/17 15:51:21 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void throw_err(t_cub *cub, char *err)
{
    printf("Error\n%s\n", err);
    free(cub);
    exit(0);
}

int	save_map(char **acc, char *line)
{
	char	*new;

	if (!line || *line == '\0')
	{
        if(line)
		    free(line);
		return (0);
	}
	new = ft_strjoin(*acc, line);
	*acc = new;
	free(line);
	return (1);
}

int check_file_ext(char *file)
{
    char *dot;

    dot = ft_strrchr(file, '.');
    if(!dot)
        return(printf("Error\nNo file extension\n"),1);
    if(ft_strcmp(dot, ".cub") != 0)
        return(printf("Error\nInvalid file extension\n"),1);
    return(0);
}