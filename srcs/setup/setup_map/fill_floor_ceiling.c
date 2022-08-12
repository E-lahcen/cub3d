/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:39:00 by zwina             #+#    #+#             */
/*   Updated: 2022/08/12 10:28:12 by lelhlami         ###   ########.fr       */
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

void	rgb_validator(char *str)
{
	char	**tmp;
	char	*tmp1;
	int		cnt;
	size_t	j;

	j = skip_end_whitespaces(str, 1);
	tmp1 = ft_substr(str, 0, j);
	tmp = ft_split(tmp1, ',');
	cnt = 0;
	while (tmp[cnt])
	{
		if (check_is_rgb(tmp[cnt]) || cnt == 3)
			errors("PROVIDE VALID RGB COLORS!", NULL);
		free(tmp[cnt]);
		cnt++;
	}
	if (cnt != 3)
		errors("PROVIDE 3 RGB COLORS", NULL);
	free(tmp);
	free(tmp1);
}

int	check_is_rgb(char *num)
{
	size_t	i;
	size_t	j;

	i = skip_begin_whitespaces(num, 1) - 1;
	j = skip_end_whitespaces(num, 1);
	while (++i < ft_strlen(num) && i < j)
	{
		if (!ft_isdigit(num[i]) || ft_atoi(num) < 0 || ft_atoi(num) > 255)
			return (1);
	}
	return (0);
}

int	check_comma(char *str)
{
	int cnt;

	cnt = 0;
	while (str)
	{
		if (*str == ',')
			cnt++;
		if (cnt > 2)
			return (1);
		str++;
	}
	return (0);
}