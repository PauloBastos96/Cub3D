/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:50:33 by paulorod          #+#    #+#             */
/*   Updated: 2023/11/17 15:20:20 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"

int		check_file_ext(char *file);
int		save_map(char **acc, char *line);
int		ft_isvalid(char **map, int y, int x);
int		line_lenght(char *line);
int		check_map_walls(char **map, int i, int j, t_cub *cub);
int		check_valid(t_cub *cub);
void	read_map(t_cub *cub, char *file);
void	define_line_limiter(t_cub *cub);
void	check_valid_line(char **map, int y, int x, t_cub *cub);
void	set_player_direction(t_player *player, char dir);
void	check_player(char *line, int *counter);
void	set_player_pos_and_dir(t_cub *cub, int i, int j);
void	check_player_count(int counter, char **map, t_cub *cub);
char	**set_map_even(t_cub *cub);
t_rgb	*get_color(char *line);

#endif
