/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:39:11 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/26 13:39:42 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

///Get time of day in miliseconds
/// @return Time of day in miliseconds
uint64_t	gettimeofday_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

///Get time since last update
/// @return Time since last update
uint64_t	delta_time(void)
{
	static uint64_t	last_update = 0;
	uint64_t		current_time;
	uint64_t		delta;

	current_time = gettimeofday_ms();
	if (last_update == 0)
		last_update = current_time - 1;
	delta = current_time - last_update;
	last_update = current_time;
	return (delta);
}
