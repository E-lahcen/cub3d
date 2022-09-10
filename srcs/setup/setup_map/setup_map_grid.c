/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:35:35 by zwina             #+#    #+#             */
/*   Updated: 2022/09/03 11:38:24 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_map(t_mlx *mlx, t_map *map, t_list *file_content)
{
	size_t	i;
	char	is_complete;

	is_complete = 0;
	while (file_content && is_complete < 7)
	{
		i = skip_begin_whitespaces(file_content->content, 1);
		if (((char *)file_content->content)[i] && \
				compare_texture(&((char *)file_content->content)[i]))
			(check_redendency(&((char *)file_content->content)[i], \
			file_content), fill_texture(mlx, map, \
			&((char *)file_content->content)[i]), is_complete++);
		else if (((char *)file_content->content)[i] && \
				(!ft_strncmp(&((char *)file_content->content)[i], "C", 1) || \
				!ft_strncmp(&((char *)file_content->content)[i], "F", 1)))
			(check_redendency(&((char *)file_content->content)[i], \
			file_content), fill_floor_ceiling(map, \
			&((char *)file_content->content)[i]), is_complete++);
		else if (((char *)file_content->content)[i] && is_complete == 6)
			(fill_map(map, file_content), is_complete++);
		else if (((char *)file_content->content)[i] != '\0')
			errors("Invalid charachters inside map !", NULL);
		file_content = file_content->next;
	}
	if (is_complete < 7)
		errors("Invalid map", "an element is missing");
}

void	setup_grid(t_map *map, t_player *player)
{
	size_t	i;
	size_t	j;

	map->grid = (t_block **)malloc(sizeof(t_block *) * map->height);
	i = 0;
	while (i < map->height)
		map->grid[i++] = (t_block *)malloc(sizeof(t_block) * map->width);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			map->grid[i][j].top_left.y = i * GAP;
			map->grid[i][j].top_left.x = j * GAP;
			map->grid[i][j].bottom_right.y = i * GAP + GAP;
			map->grid[i][j].bottom_right.x = j * GAP + GAP;
			map->grid[i][j].c = map->map[i][j];
			if (is_player(map->grid[i][j].c))
				fill_player(player, &map->grid[i][j], i, j);
		}
	}
}

int	compare_texture(char *str)
{
	if (!ft_strncmp(str, "NO", 2) || \
		!ft_strncmp(str, "SO", 2) || \
		!ft_strncmp(str, "WE", 2) || \
		!ft_strncmp(str, "EA", 2))
		return (1);
	return (0);
}

void	check_redendency(char *texture, t_list	*file_content)
{
	t_list	*tmp_list;
	char	*tmp_str;

	tmp_list = file_content->next;
	while (tmp_list && texture)
	{
		tmp_str = (char *)tmp_list->content;
		if (!ft_strncmp(texture, tmp_str + \
		skip_begin_whitespaces(tmp_str, 1), 2))
			errors("DUPLICATED TEXTURES", NULL);
		tmp_list = tmp_list->next;
	}
}
