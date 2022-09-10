/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:24:39 by lelhlami          #+#    #+#             */
/*   Updated: 2022/09/02 21:03:58 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int mouse_move(int x, int y, void *data)
{
    (void)y;

    if (x > 0 && x < SCREENWIDTH)
    {   
        if (x > 4 * SCREENWIDTH / 6)
            (key_look(LOOK_RIGHT, data), x++);
        else if (x < 2 * SCREENWIDTH / 6)
            (key_look(LOOK_LEFT, data), x--);
    }
    return (0);
}