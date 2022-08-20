/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:58:02 by zwina             #+#    #+#             */
/*   Updated: 2022/08/13 16:55:50 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map(t_map *map, t_list *file_content)
{
	size_t	offset;
	size_t	i;

	offset = set_height_width(map, file_content);
	map->map = (char **)malloc(sizeof(char *) * map->height);
	i = 0;
	while (i < map->height)
	{
		map->map[i] = (char *)malloc(sizeof(char) * map->width);
		filling_map(map->map[i], (char *)file_content->content + offset, \
					map->width);
		file_content = file_content->next;
		i++;
	}
	map_validation(map);
}

size_t	set_height_width(t_map *map, t_list *file_content)
{
	size_t	offset;
	size_t	i;

	map->height = 0;
	map->width = 0;
	offset = -1;
	while (file_content)
	{
		i = skip_begin_whitespaces(file_content->content, 0);
		if (offset > i)
			offset = i;
		if (((char *)file_content->content)[i] == '\0')
			errors("Invalid map", "empty line in map");
		i = skip_end_whitespaces(file_content->content, 0);
		if (i > map->width)
			map->width = i;
		file_content = file_content->next;
		map->height++;
	}
	map->width -= offset;
	return (offset);
}
