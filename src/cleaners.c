/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:27:19 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/23 15:08:04 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/// Free a split array
/// @param split Split array
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

/// Free the map
/// @param cub Cub struct
void	free_map(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map[i])
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
}
