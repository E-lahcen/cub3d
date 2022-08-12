#include "cub3d.h"

void	print_map(t_map *map)
{
	printf("\nF %d,%d,%d.\n", map->floor.r, map->floor.g, map->floor.b);
	printf("C %d,%d,%d.\n", map->ceiling.r, map->ceiling.g, map->ceiling.b);
	printf("map height == %zu.\n", map->height);
	printf("map width == %zu.\n\n", map->width);
	for (size_t i = 0; i < map->height; i++)
	{
		for (size_t j = 0; j < map->width; j++)
		{
			if (map->map[i][j])
				ft_putchar_fd(map->map[i][j], 1);
			else
				ft_putchar_fd('.', 1);
		}
		ft_putchar_fd('\n', 1);
	}
}
