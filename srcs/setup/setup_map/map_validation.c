/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:01:49 by lelhlami          #+#    #+#             */
/*   Updated: 2022/08/07 16:14:11 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//check validate characters : N E S W 0 1 \0 in the same time 
//check number of players
//check map should be surrounded by walls
//check \0 is surrounded by \0 or 1

void	map_validation(t_map *big_map)
{
	check_valid_symbols(big_map);
	check_number_players(big_map);
	check_map_borders(big_map);
}

void	check_number_players(t_map *big_map)
{
	size_t	i;
	size_t	j;
	int		n;
	char	**tmp_map;

	i = 0;
	n = 0;
	tmp_map = big_map->map;
	while (i < big_map->height)
	{
		j = 0;
		while (j < big_map->width)
		{
			if (is_player(tmp_map[i][j]))
				n++;
			j++;
		}
		i++;
	}
	if (n != 1)
		errors("Check number of players!", NULL);
}

void	check_valid_symbols(t_map *big_map)
{
	size_t	i;
	size_t	j;
	char	**tmp_map;

	i = 0;
	tmp_map = big_map->map;
	while (i < big_map->height)
	{
		j = 0;
		while (j < big_map->width)
		{
			if (tmp_map[i][j] != '\0' && \
				tmp_map[i][j] != 'N' && \
				tmp_map[i][j] != 'E' && \
				tmp_map[i][j] != 'S' && \
				tmp_map[i][j] != 'W' && \
				tmp_map[i][j] != '0' && \
				tmp_map[i][j] != '1')
				errors("Invalid symbol inside the map", NULL);
			j++;
		}
		i++;
	}
}

void	check_map_borders(t_map *big_map)
{
	size_t	i;
	size_t	j;
	char	**tmp_map;

	i = 0;
	tmp_map = big_map->map;
	while (i < big_map->height)
	{
		j = 0;
		while (!tmp_map[i][j])
			j++;
		while (j < big_map->width)
		{
			if (tmp_map[i][j])
				if (((!i || i == big_map->height - 1) && \
				(tmp_map[i][j] != '1' && tmp_map[i][j])) \
				|| (tmp_map[i][j] != '1' && check_valid_place(tmp_map, i, j)))
					errors("Please check map borders!", NULL);
			j++;
		}
		i++;
	}
}

int	check_valid_place(char **map, size_t i, size_t j)
{
	if (!map[i][j] || \
		!map[i - 1][j - 1] || \
		!map[i - 1][j] || \
		!map[i - 1][j + 1] || \
		!map[i][j - 1] || \
		!map[i][j + 1] || \
		!map[i + 1][j - 1] || \
		!map[i + 1][j] || \
		!map[i + 1][j + 1])
		return (1);
	return (0);
}
