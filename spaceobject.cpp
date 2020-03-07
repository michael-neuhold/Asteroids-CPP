#include "spaceobject.h"
#include <cmath>

spaceobject::spaceobject(wxPoint pos, int degree) 
	:	position{pos},
		degree{degree}
{}


void spaceobject::move(wxSize size) {
	dx_speed = sin(degree * M_PI / 180) * 2;
	dy_speed = -cos(degree * M_PI / 180) * 2;
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

void spaceobject::stay_in_universe(wxSize size) {
	if (position.x >= size.x) position.x = 0;
	else if (position.x == 0) position.x = size.x;
	else if (position.y >= size.y) position.y = 0;
	else if (position.y == 0) position.y = size.y;
}