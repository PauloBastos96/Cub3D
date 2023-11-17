/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:01:54 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/16 16:03:15 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANERS_H
# define CLEANERS_H

# include "structs.h"

void	free_split(char **split);
void	free_colors(t_cub *cub);
void	exit_game(t_cub *cub);
void	throw_err(char *err, t_cub *cub);

#endif
