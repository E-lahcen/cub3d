/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:23:28 by zwina             #+#    #+#             */
/*   Updated: 2022/08/31 11:59:54 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>

# include "libft.h"
# include "get_next_line.h"

# define PI 3.1415926535
# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define MINIMAPHEIGHT 210
# define MINIMAPWIDTH 210
# define GAP 64
# define MINIGAP 10
# define HFOV 0.523598775

# define NO 1
# define EA 2
# define SO 3
# define WE 4

# define UP 13
# define RIGHT 2
# define DOWN 1
# define LEFT 0
# define LOOK_RIGHT 124
# define LOOK_LEFT 123

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}			t_rgb;

typedef struct s_point
{
	double	x;
	double	y;
	t_rgb	color;
}			t_point;

typedef struct s_ray
{
	size_t	x;
	size_t	y;
	t_point	rp;
	double	dis;
}			t_ray;

typedef struct s_player
{
	size_t	x;
	size_t	y;
	t_point	pos;
	t_point	dir;
	t_point	sid;
	double	angle;
}			t_player;

typedef struct s_txr
{
	t_img	img;
	int		height;
	int		width;
}			t_txr;

typedef struct s_block
{
	t_point	top_left;
	t_point	bottom_right;
	char	c;
}			t_block;

typedef struct s_map
{
	t_block	**grid;
	t_block	**mini_grid;
	char	**map;
	char	**mini_map;
	size_t	width;
	size_t	height;
	t_rgb	floor;
	t_rgb	ceiling;
	t_txr	no;
	t_txr	ea;
	t_txr	so;
	t_txr	we;
}			t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}			t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
}			t_data;

//		main.c
void	errors(char *str, char *str_error);
int		close_window(void *param);
//		my_mlx_pixel_put.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		get_color_from_img(t_img *img, int x, int y);
//		HOOKS
//			hooks.c	
int		key_hooks(int key_code, void *param);
void	re_draw(t_data *data);
//			move.c
void	move(int key_code, t_data *data);
void	set_translater(int key_code, t_player *player, t_point *to_go);
char	can_he_move_to(t_point *to_go, t_map *map, t_player *player);
void	moving(t_player *player, t_point *to_go);
void	player_in_grid(t_map *map, t_player *player);
//			key_look.c
void	key_look(int key_code, t_data *data);
//		SETUP
//			setup_data.c
void	setup_data(t_data *data, char *filename);
void	extension_validation(char *filename);
t_list	*read_filename(char *filename);
void	remove_last_empty(t_list *lst);
void	mlx_initializer(t_mlx *mlx);
//			SETUP_MAP
//				map_validation.c
void	map_validation(t_map *big_map);
void	check_valid_symbols(t_map *big_map);
void	check_map_borders(t_map *big_map);
int		check_valid_place(char **map, size_t i, size_t j);
void	check_number_players(t_map *big_map);
//				setup_map_grid.c
void	setup_map(t_mlx *mlx, t_map *map, t_list *file_content);
void	setup_grid(t_map *map, t_player *player);
void	check_redendency(char *texture, t_list	*file_content);
int		compare_texture(char *str);
//				fill_player.c
char	is_player(char c);
void	fill_player(t_player *player, t_block *block, size_t y, size_t x);
void	fill_player_dir_sid(t_player *player);
//				fill_map.c
void	fill_map(t_map *map, t_list *file_content);
size_t	set_height_width(t_map *map, t_list *file_content);
//				fill_map_utils.c
void	filling_map(char *map_line, char *file_line, size_t size);
size_t	skip_begin_whitespaces(char *str, char with_tab);
size_t	skip_end_whitespaces(char *str, char with_tab);
//				fill_texture.c
void	fill_texture(t_mlx *mlx, t_map *map, char *str);
void	*get_img_texture(t_txr *side, char *filename, void *mlx);
void	texture_validation(char *str);
//				fill_floor_ceilling.c
void	fill_floor_ceiling(t_map *map, char *str);
void	fill_ceiling(t_map *map, char *str);
void	fill_floor(t_map *map, char *str);
//				fill_floor_ceilling_utils.c
void	rgb_validator(char *str);
int		check_is_rgb(char *num);
int		check_comma(char *str);
//		DRAW
//			DRAW_MINIMAP
void		draw_mini_map(t_data *data);
void    	draw_mini_map_player(t_data *data);
void		draw_mini_blocks(t_data *data, t_point p1, t_point p2, t_point *circle);
int			verify_in_circle(double x, double y);
//			DRAW_MINIMAP_UTILS
void	    set_mini_map(t_data *data);
void		mini_setup_grid(t_data *data);
void		print_maps(t_data *data);
void		free_double(t_data *data);

//		draw.c
void	draw(t_data *data);
double	get_pos_angle(double angle);
//		raycasting.c
void	draw_rays(t_data *data);
int	is_pn_in_blk(t_block *block, t_point *point);
double	distance(t_point *p1, t_point *p2);
t_point	get_range(double x, double y);
double	mapping(double p, t_point in, t_point out);
//		raycast_x.c
void	raycast_x(t_ray *ray, t_map *map, t_player *player, double r_angle);
void	raycast_x_right(t_ray *ray, t_map *map, t_player *player, \
						double r_angle);
void	raycast_x_left(t_ray *ray, t_map *map, t_player *player, \
						double r_angle);
char	ray_hit_x(t_map *map, t_ray *ray, char side);
//		raycast_y.c
void	raycast_y(t_ray *ray, t_map *map, t_player *player, double r_angle);
void	raycast_y_up(t_ray *ray, t_map *map, t_player *player, \
						double r_angle);
void	raycast_y_down(t_ray *ray, t_map *map, t_player *player, \
						double r_angle);
char	ray_hit_y(t_map *map, t_ray *ray, char side);
//		draw_ray_x.c
void	draw_ray_x(t_ray *ray, t_data *data, double angle);
//		draw_ray_y.c
void	draw_ray_y(t_ray *ray, t_data *data, double angle);
//		draw_line.c
void	draw_line(t_img *img, t_point *begin, t_point *end, int color);
void	draw_line_texture(t_img *img, t_txr *txr, t_point *p, int row);
double	setup_draw_line(t_point *begin, t_point *end, \
						t_point *middle, t_point *d);
int		get_rgb(t_rgb color);

# include "print.h"
#endif
