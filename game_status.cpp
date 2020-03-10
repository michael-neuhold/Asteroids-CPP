#include "game_status.h"

game_status::game_status(int live_counter)
	:	life_counter{ live_counter },
		hit_counter{0}
{
	for (int i = 0; i < live_counter; i++) {
		spaceships.add(new spaceship({status_position.x + i * 40,status_position.y}, 0, false));
	}
}

game_status::~game_status() {
	// nothing to do
}

int game_status::get_life_counter() const {
	return life_counter;
}

int game_status::get_hit_counter() const {
	return hit_counter;
}

void game_status::draw(context& con) const {
	for (int i = 0; i < life_counter; i++) spaceships[i]->draw(con);
	con.SetTextForeground(*wxWHITE);
	con.DrawText("Asteroids", { con.GetSize().x - 100,20 });
}

void game_status::decrease_life_counter() {
	life_counter--;
}

