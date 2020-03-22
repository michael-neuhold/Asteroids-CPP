#include "game_status.h"

/* GENERAL ============================================ */
game_status::game_status(int live_counter)
: life_counter{ live_counter },
  hit_counter{0}
{
	for (int i = 0; i < live_counter; i++) {
		spaceships.add(new spaceship({status_position.x + i * 40,status_position.y}, 0, false));
	}
}

game_status::~game_status() { }

/* DRAW =============================================== */
void game_status::draw(context& con) const {
	for (int i = 0; i < life_counter; i++) spaceships[i]->draw(con);
}

/* UPDATE STATE ======================================= */
void game_status::decrease_life_counter() {
	if (--life_counter == 0) game_over = true;
}

void game_status::increase_hit_counter() {
	hit_counter++;
}

/* GETTERS ============================================ */
bool game_status::is_game_over() const {
	return game_over;
}

int game_status::get_life_counter() const {
	return life_counter;
}

int game_status::get_hit_counter() const {
	return hit_counter;
}