/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:39:00 by zwina             #+#    #+#             */
/*   Updated: 2022/08/12 11:11:19 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_floor_ceiling(t_map *map, char *str)
{
	if (!ft_strncmp(str, "C", 1))
		fill_ceiling(map, str + skip_begin_whitespaces(str + 1, 1));
	else if (!ft_strncmp(str, "F", 1))
		fill_floor(map, str + skip_begin_whitespaces(str + 1, 1));
}

void	fill_ceiling(t_map *map, char *str)
{
	size_t	i;

	i = skip_begin_whitespaces(str, 1);
	rgb_validator(str + i);
	if (!str[i] && !str[i + 1])
		errors("Invalid map", "error ceilling element");
	map->ceiling.r = ft_atoi(str + i);
	while (str[i] && str[i] != ',')
		i++;
	if (!str[i] && !str[i + 1])
		errors("Invalid map", "error ceilling element");
	map->ceiling.g = ft_atoi(str + ++i);
	while (str[i] && str[i] != ',')
		i++;
	if (!str[i] && !str[i + 1])
		errors("Invalid map", "error ceilling element");
	map->ceiling.b = ft_atoi(str + ++i);
}

void	fill_floor(t_map *map, char *str)
{
	size_t	i;

	i = skip_begin_whitespaces(str, 1);
	rgb_validator(str + i);
	if (!str[i] && !str[i + 1])
		errors("Invalid map", "error floor element");
	map->floor.r = ft_atoi(str + i);
	while (str[i] && str[i] != ',')
		i++;
	if (!str[i] && !str[i + 1])
		errors("Invalid map", "error floor element");
	map->floor.g = ft_atoi(str + ++i);
	while (str[i] && str[i] != ',')
		i++;
	if (!str[i] && !str[i + 1])
		errors("Invalid map", "error floor element");
	map->floor.b = ft_atoi(str + ++i);
}
