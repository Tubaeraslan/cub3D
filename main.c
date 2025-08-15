#include "cub3d.h"
#include <stdio.h>
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
    "1000000001",
    "1010000001",
    "1010000001",
    "1111111111",
    NULL
	};
	data->map = map_example;
	data->player->posX = 2;
	data->player->posY = 2;
	data->player->start_pos = 'N';
	data->player->mapX=2;
	data->player->mapY=2;
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
	//raycasting
	/*
		her dikey piksel çizgisi için ray gönder
		ray hangi hücreye çarpana kadar ilerliyo hesapla
		çarpma mesafesine göre duvar yüksekliği çiz
		texture koordinatlarını hesapla
	*/
	raycasting(data->player);
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
