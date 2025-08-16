#include "cub3d.h"
#include <stdio.h>

void	load_textures(t_data *data)
{
    data->tex_north = mlx_xpm_file_to_image(data->mlx, "./textures/north.xpm", &data->text_width, &data->text_height);
    data->tex_south = mlx_xpm_file_to_image(data->mlx, "./textures/south.xpm", &data->text_width, &data->text_height);
    data->tex_east  = mlx_xpm_file_to_image(data->mlx, "./textures/east.xpm",  &data->text_width, &data->text_height);
    data->tex_west  = mlx_xpm_file_to_image(data->mlx, "./textures/west.xpm",  &data->text_width, &data->text_height);
}

int	key_press(int keycode, t_data *data)
{
    double newX = data->player->posX;
    double newY = data->player->posY;

    if (keycode == 53) // ESC tuşu
        exit(0);
    if (keycode == 13) // W
        newY -= 0.1;
    if (keycode == 1) // S
        newY += 0.1;
    if (keycode == 0) // A
        newX -= 0.1;
    if (keycode == 2) // D
        newX += 0.1;

    // Harita sınırı ve duvar kontrolü
    if (data->map[(int)newY][(int)newX] != '1')
    {
        data->player->posX = newX;
        data->player->posY = newY;
    }
    // Ekranı tekrar çiz
    raycasting(data->player);
    return (0);
}

int main()
{
	t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (1); // malloc hatası

    data->player = malloc(sizeof(t_player)); // burayı eklemelisin
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
	//map okuma parser
	//map doğrulama
	//minilibx hazırlama
	//oyuncu pozisyonu doğrulama
	/*
	dirX - dirY oyuncunun baktığı yön vektörü
	planeX - planeY ekranın sağ ve sol kenarlerını temsil eden
					görüş alanı(FOV)field of view-genelde 66 derece kaul edilir- genişliğini belirleyen vektör
	plane vektörü dir vektörüne dik (90 derece) döndürülmüş vektördür

	örnek:
	dirX = cos(angle)
	dirY = sin(angle)

	planeX = -dirY * tan(FOV / 2)
	planeY = dirX * tan(FOV / 2)
	*/
	player_position(data->player);
	data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, screenWidth, screenHeight, "cub3d");
	load_textures(data);
	mlx_key_hook(data->win, key_press, data);
	//raycasting
	/*
		her dikey piksel çizgisi için ray gönder
		ray hangi hücreye çarpana kadar ilerliyo hesapla
		çarpma mesafesine göre duvar yüksekliği çiz
		texture koordinatlarını hesapla
	*/
	raycasting(data->player);
	mlx_loop(data->mlx);
	/*
	eğer player sağa bakıyosa dirX=1 dirY=0. planeX=0 planeY = 0.66(fov genişliği)
	*/
	//ışın gönderme kameranın sol ucundan sağ ucuna yayılır
	//kontrolleri ayarla wsad
	mlx_loop(data->mlx);
	printf("Player position: (%f, %f)\n", data->player->posX, data->player->posY);
	printf("Player direction: (%f, %f)\n", data->player->dirX, data->player->dirY);
	return 0;
}
