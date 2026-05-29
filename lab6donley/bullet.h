//Lucia Donley
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>


class bullet
{
public:
	bullet();
	void fire();
	int move_bullet(int arrowX, int arrowY, int width, int length, int height);

	//added following function
	void create_bullet_bitmap(ALLEGRO_DISPLAY* display);

	void erase_bullet();
	bool getStatus();
private:
	int x, y;
	bool alive;
	//added following variable
	ALLEGRO_BITMAP* bullet_bmp;
};

