/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:24:27 by paulorod          #+#    #+#             */
/*   Updated: 2023/10/24 12:54:39 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Join s1 and s2, replacing s1*/
char	*ft_strrep(char *s1, char *s2)
{
	char	*new;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (s1);
	if (!s1 && !s2)
		return (NULL);
	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}
