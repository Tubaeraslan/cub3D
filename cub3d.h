/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:56:14 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/27 14:43:17 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include "math.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080
# define M_PI 3.14159265358979323846
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_move
{
	double			new_x;
	double			new_y;
}					t_move;

typedef struct s_draw
{
	int				x;
	int				draw_start;
	int				draw_end;
	double			wall_dist;
}					t_draw;

typedef struct s_tex_calc
{
	int				tex_x;
	double			step;
	double			tex_pos;
}					t_tex_calc;

typedef struct s_skyfloor
{
	int				x;
	int				draw_start;
	int				draw_end;
	int				sky_color;
	int				ground_color;
	int				*img_data;
	int				size_line;
}					t_skyfloor;

typedef struct s_texture
{
	void			*img;
	int				*addr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	char			start_pos;
	double			fov;
	double			plane_x;
	double			plane_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				hit;
	int				side;
	int				player_x;
	int				player_y;
	int				move_forward;
	int				move_backward;
	int				move_left;
	int				move_right;
	int				turn_left;
	int				turn_right;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct s_map
{
	char			*map_line;
	int				num;
	struct s_map	*next;
}					t_map;

typedef struct s_feature
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*f;
	char			*c;
}					t_feature;

typedef struct s_data
{
	t_feature		*feature;
	t_player		*player;
	t_map			*map;
	int				high;
	int				widht;
	char			**char_map;
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
	char			**fakemap;
	int				line_num;
	void			*mlx;
	void			*win;
	bool			empty;
	int				text_width;
	int				text_height;
}					t_data;

int					is_true_map(t_data *data, int fd);
int					is_feature(char *line, t_data *data);
int					feature_ctl(t_data *data);
void				clear_array(char **array);
void				freegnl(int fd);
int					jumper(char c);
int					check_map_name(char *str);
int					check_map(char **av, t_data *data);
t_map				*ft_mapnew(char *content, int line_num);
void				map_add_back(t_map **lst, t_map *new);
int					ft_mapsize(t_map *lst);
int					is_exe(char *str);
int					rgb_atoi(const char *str);
int					is_truedigit(char *str, int val, int i, int count);
char				**copy_char_matrix(char **src, int i);
void				free_data(t_data *data, int i);
void				execute(t_data *data);
int					exit_program(t_data *data);
void				list_to_char(t_data *data);
void				find_player_position(char **map, t_data *data);
void				draw_image(t_data *data);
void				dda_algorithm(t_data *data);
double				find_wall_distance(t_player *player);
void				draw_wall_line(t_data *data, int *img_data, int line,
						t_draw draw);
t_texture			*choose_texture(t_data *data);
void				player_position(t_player *player);
void				strip_whitespace(char *str);
char				*parse_texture_path(char *path, const char *prefix);
void				ray_dist(t_player *player);
void				side_ray(t_player *player);
int					rgb_str_to_int(const char *str);
void				ray_measure(int x, int w, t_data *data);
void				sky_floor(t_skyfloor ts, t_data *data);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);
int					game_loop(void *param);
void				move_player(t_data *data);
void				rotate_player(t_player *p, double angle);
void				free_mlx(t_data *data);
void				ff_double(char **map, int x, int y, t_data *data);
int					ff_empty(char **a, char c);
#endif