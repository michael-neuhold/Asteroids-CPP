#pragma once

#include <ml5/ml5.h>
#include "spaceship.h"

class game_status {

public:
	using context = ml5::paint_event::context_t;

	game_status(int life_counter);
	~game_status();

	int get_life_counter() const;
	void draw(context& con) const;
	int get_hit_counter() const;

private: 

	int life_counter;
	int hit_counter;
	wxPoint status_position{20,20};
	

	ml5::vector<spaceship*> spaceships;

};