#include "bullet.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

bullet::bullet()
{
	//bullet_bmp= al_create_bitmap(8, 8);
	alive = false;
	srand(time(0));
}
bool bullet::getStatus()
{
	return alive;
}

void bullet::fire()
{
	x = rand() % 615 + 10;
	y = 10;
	alive = true;

}
void bullet::erase_bullet()
{
	al_draw_filled_rectangle(x, y, x + 5, y + 5, al_map_rgb(0, 0, 0)); //black color
}
void bullet::create_bullet_bitmap(ALLEGRO_DISPLAY* display) {
	
	bullet_bmp = al_create_bitmap(8, 8);
	if (!bullet_bmp) {
		exit(1);
		al_destroy_display(display);

	}
	al_set_target_bitmap(bullet_bmp);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(x, y, x + 5, y + 5, al_map_rgb(255, 255, 0));//yellow color
	al_draw_filled_circle(x + 2, y + 2, 3, al_map_rgb(255, 255, 0));
}
int bullet::move_bullet(int arrowX, int arrowY, int width, int length, int height)
{
	
	

	y++;
	al_draw_bitmap(bullet_bmp, x, y, 0);


	if (x > arrowX && x < arrowX + width && y > arrowY && y < arrowY + length) {
		al_draw_filled_rectangle(x, y, x + 5, y + 5, al_map_rgb(0, 0, 0)); //BLACK
		alive = false;
		return 1;
	}
	if (y > height)
		alive = false;
	return 0;


}




