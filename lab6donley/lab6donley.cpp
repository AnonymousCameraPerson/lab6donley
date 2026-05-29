
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "arrow.h";
#include "bullet.h"
#include <stdio.h>
//Lucia Donley
int main(void)
{
	arrowClass arrow;
	bullet mybullet[10];

	int score = 0;
	bool redraw = true;
	const int FPS = 60;

	//variables
	int width = 640;
	int height = 480;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	if (!al_init()) {
		printf("Failed to initialize Allegro!\n");
		return -1;
	}
	//added following code to initialize ttf addon
	al_init_font_addon();

	if (!al_init_ttf_addon()) {
		printf("Failed to initialize ttf addon.\n");
		return -1;
	}

	//added font here
	ALLEGRO_FONT* font = al_load_ttf_font("college.ttf", 36, 0);

	if (!font) {
		printf("Failed to load font!\n");
		al_destroy_display(display);
		return -1;
	}

	arrow.create_arrow_bitmap(display);
	//created bitmaps for bullets
	for (int i = 0;i < 10;i++) {
		mybullet[i].create_bullet_bitmap(display);
	}
	//onebullet.create_bullet_bitmap(display);



	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	arrow.drawArrow();
	al_flip_display();
	al_start_timer(timer);
	while (!done)
	{
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			//set program to run for 30 seconds
			al_set_timer_count(timer,al_get_timer_count(timer) + 1);
			int64_t sometime = al_get_timer_count(timer);
			int64_t curTime = sometime / 117;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//print time and score to screen
			al_draw_textf(font, al_map_rgb(255, 255, 255), 3, 10, 0, "Timer: %lld", 30-curTime);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 485, 10, 0, "Score: %i", score);
			al_flip_display();
			
			if (curTime ==30) {
				break;
			}
			redraw = true;
			for (int i = 0;i < 10;i++)
			{
				if (!mybullet[i].getStatus()) {
					mybullet[i].fire();
				}
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				arrow.up();
				break;
			case ALLEGRO_KEY_DOWN:
				arrow.down();
				break;
			case ALLEGRO_KEY_LEFT:
				arrow.left();
				break;
			case ALLEGRO_KEY_RIGHT:
				arrow.right();
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if (arrow.getSpeed() != 0) {
				arrow.erase_arrow();
				arrow.move_arrow(width, height);
			}
			arrow.drawArrow();
			for (int i = 0;i < 10;i++)
			{
				mybullet[i].erase_bullet();
				score += mybullet[i].move_bullet(arrow.getX(), arrow.getY(), 16, 16, height);
			}
		}
		al_flip_display();
	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}
