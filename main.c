#include "cub3d.h"
#include <stdio.h>

int	key_hook(int keycode, t_data *data)
{
	// Linux: W=119, S=115, A=97, D=100, ESC=65307
	double moveSpeed = 0.1;
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) // W
	{
		double newX = data->player->posX + data->player->dirX * moveSpeed;
		double newY = data->player->posY + data->player->dirY * moveSpeed;
		if (newX >= 0 && newX < data->map_width && newY >= 0 && newY < data->map_height && data->map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	if (keycode == 115) // S
	{
		double newX = data->player->posX - data->player->dirX * moveSpeed;
		double newY = data->player->posY - data->player->dirY * moveSpeed;
		if (newX >= 0 && newX < data->map_width && newY >= 0 && newY < data->map_height && data->map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	if (keycode == 97) // A (sola strafe)
	{
		double newX = data->player->posX - data->player->planeX * moveSpeed;
		double newY = data->player->posY - data->player->planeY * moveSpeed;
		if (newX >= 0 && newX < data->map_width && newY >= 0 && newY < data->map_height && data->map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	if (keycode == 100) // D (sağa strafe)
	{
		double newX = data->player->posX + data->player->planeX * moveSpeed;
		double newY = data->player->posY + data->player->planeY * moveSpeed;
		if (newX >= 0 && newX < data->map_width && newY >= 0 && newY < data->map_height && data->map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	double rotSpeed = 0.08;
	if (keycode == 65363) // Sağ ok tuşu (right arrow)
	{
		double oldDirX = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(rotSpeed) - data->player->dirY * sin(rotSpeed);
		data->player->dirY = oldDirX * sin(rotSpeed) + data->player->dirY * cos(rotSpeed);
		double oldPlaneX = data->player->planeX;
		data->player->planeX = data->player->planeX * cos(rotSpeed) - data->player->planeY * sin(rotSpeed);
		data->player->planeY = oldPlaneX * sin(rotSpeed) + data->player->planeY * cos(rotSpeed);
	}
	if (keycode == 65361) // Sol ok tuşu (left arrow)
	{
		double oldDirX = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(-rotSpeed) - data->player->dirY * sin(-rotSpeed);
		data->player->dirY = oldDirX * sin(-rotSpeed) + data->player->dirY * cos(-rotSpeed);
		double oldPlaneX = data->player->planeX;
		data->player->planeX = data->player->planeX * cos(-rotSpeed) - data->player->planeY * sin(-rotSpeed);
		data->player->planeY = oldPlaneX * sin(-rotSpeed) + data->player->planeY * cos(-rotSpeed);
	}
	draw_image(data); // Ekranı güncelle
	return (0);
}

void	load_textures(t_data *data)
{
	data->tex_north = mlx_xpm_file_to_image(data->mlx, "./textures/north.xpm", &data->text_width, &data->text_height);
	data->tex_south = mlx_xpm_file_to_image(data->mlx, "./textures/south.xpm", &data->text_width, &data->text_height);
	data->tex_east  = mlx_xpm_file_to_image(data->mlx, "./textures/east.xpm",  &data->text_width, &data->text_height);
	data->tex_west  = mlx_xpm_file_to_image(data->mlx, "./textures/west.xpm",  &data->text_width, &data->text_height);
	if (!data->tex_north || !data->tex_south || !data->tex_east || !data->tex_west) {
		fprintf(stderr, "[ERROR] Texture dosyalarindan biri yuklenemedi! Dosya yollarini ve formatlarini kontrol edin.\n");
		exit(1);
	}
}

// Basit image buffer ile çizim için fonksiyon
void draw_image(t_data *data)
{
	void *img;
	int *img_data;
	int bpp, size_line, endian;

	img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	if (!img)
	{
		fprintf(stderr, "[ERROR] Image buffer olusturulamadi!\n");
		return;
	}
	img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	raycasting(data->player, img_data, size_line);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}

int	exit_program(t_data *data)
{
	(void)data;
    //free
    exit(0);
    return (0);
}

int main()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (1);
	data->player->data = data;
	data->player->fov = 0.66;
	char *map_example[] = {
	"1111111111",
	"1010000101",
	"1000100001",
	"1010100001",
	"1010000011",
	"1111111111",
	NULL
	};
	int map_width = 10;
	int map_height = 6;
	data->map_width = map_width;
	data->map_height = map_height;
	data->player->hit = 0;
	data->map = map_example;
	data->player->posX = 3.5;
	data->player->posY = 3.5;
	data->player->start_pos = 'N';
	data->player->mapX=2;
	data->player->mapY=2;
	data->text_width = 0;
	data->text_height = 0;
	player_position(data->player);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screenWidth, screenHeight, "cub3d");
	mlx_hook(data->win, 2, 1L<<0, key_hook, data);      // Key press
	mlx_hook(data->win, 17, 0, exit_program, data);
	load_textures(data);
	draw_image(data);
	mlx_loop(data->mlx);
	printf("Player position: (%f, %f)\n", data->player->posX, data->player->posY);
	printf("Player direction: (%f, %f)\n", data->player->dirX, data->player->dirY);
	return 0;
}
