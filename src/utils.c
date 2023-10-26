/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:26:32 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/10/26 12:32:25 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

///Print error message and exit game
///@param err The error message
void	throw_err(char *err, t_cub *cub)
{
	printf("%s[ERROR]\n%s%s\n", RED, err, RESET);
	if (cub)
		exit_game(cub);
	exit(1);
}
