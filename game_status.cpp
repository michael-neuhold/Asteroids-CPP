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
	if (game_over) {
		wxFont font{ con.GetFont() };
		font.SetPointSize(30);
		con.SetFont(font);
		con.SetTextForeground(*wxWHITE);
		con.DrawText("Game Over", { con.GetSize().x / 2 - 100,con.GetSize().y / 2 - 30 });
	}
}

void game_status::decrease_life_counter() {
	life_counter--;
	if (life_counter == 0) game_over = true;
}

void game_status::increase_hit_counter() {
	hit_counter++;
}

bool game_status::is_game_over() const {
	return game_over;
}
