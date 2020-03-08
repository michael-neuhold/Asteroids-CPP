#include "spaceobject.h"
#include <cmath>

spaceobject::spaceobject(wxPoint pos, int degree) 
	:	position{pos},
		degree{degree}
{}

void spaceobject::move(wxSize size) {
	dx_speed = sin(rad_of(degree)) * 2; // 5
	dy_speed = -cos(rad_of(degree)) * 2; // 5
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

void spaceobject::stay_in_universe(wxSize size) {
	if (position.x > size.x) position.x = 0;
	else if (position.x < 0) position.x = size.x;
	else if (position.y > size.y) position.y = 0;
	else if (position.y < 0) position.y = size.y;
}

bool spaceobject::is_in_universe(wxSize size) {
	return position.x <= size.x && position.x >= 0 && position.y <= size.y && position.y >= 0;
}

double spaceobject::rad_of(int deg) {
	return deg * M_PI / 180;
}