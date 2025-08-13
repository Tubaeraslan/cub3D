#include "cub3d.h"

int main(int argc, char **argv)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->fov = 0.66;
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
	player_position(player);
	//raycasting
	/*
		her dikey piksel çizgisi için ray gönder
		ray hangi hücreye çarpana kadar ilerliyo hesapla
		çarpma mesafesine göre duvar yüksekliği çiz
		texture koordinatlarını hesapla
	*/
	raycasting();
	/*
	eğer player sağa bakıyosa dirX=1 dirY=0. planeX=0 planeY = 0.66(fov genişliği)
	*/
	//ışın gönderme kameranın sol ucundan sağ ucuna yayılır
	//kontrolleri ayarla wsad
		
	return 0;
}
