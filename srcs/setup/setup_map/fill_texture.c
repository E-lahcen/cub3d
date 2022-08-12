/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:14 by zwina             #+#    #+#             */
/*   Updated: 2022/08/11 12:34:27 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_texture(t_map *map, char *str)
{
	(void)map;
	texture_validation(str + 2);
}

void	texture_validation(char *str)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = skip_begin_whitespaces(str, 1);
	j = skip_end_whitespaces(str, 1);
	tmp = ft_substr(str, i, j - i);
	if (access(tmp, R_OK) == -1)
		errors("PROBLEM AT THE TEXTURE'S PATH", NULL);
	free(tmp);
}
