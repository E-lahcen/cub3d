/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_floor_ceiling_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:39:24 by lelhlami          #+#    #+#             */
/*   Updated: 2022/08/12 11:43:58 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (cnt != 3 || check_comma(str))
		errors("PROVIDE 3 RGB COLORS", NULL);
	free(tmp);
	free(tmp1);
}

int	check_is_rgb(char *num)
{
	size_t	i;
	size_t	j;

	i = skip_begin_whitespaces(num, 1);
	j = skip_end_whitespaces(num, 1);
	if (!num[i])
		return (1);
	while (i < j)
	{
		if (!ft_isdigit(num[i]) || ft_atoi(num) < 0 || ft_atoi(num) > 255)
			return (1);
		i++;
	}
	return (0);
}

int	check_comma(char *str)
{
	int		cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			cnt++;
		if (cnt > 2)
			return (1);
		i++;
	}
	return (0);
}
