/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:23:23 by zwina             #+#    #+#             */
/*   Updated: 2022/08/27 10:43:35 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		errors("Wrong Number Of Arguments !", NULL);
	setup_data(&data, av[1]);
	draw(&data);
	mlx_hook(data.mlx.mlx_win, 2, 0, key_hooks, &data);
	mlx_hook(data.mlx.mlx_win, 17, 0, close_window, NULL);
	mlx_loop(data.mlx.mlx);
	return (0);
}

void	errors(char *str, char *str_error)
{
	ft_putendl_fd("ERROR", 2);
	ft_putstr_fd(str, 2);
	if (str_error)
	{
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(str_error, 2);
	}
	else
		ft_putchar_fd('\n', 2);
	exit(1);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
}
