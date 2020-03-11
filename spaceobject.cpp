#include "spaceobject.h"
#include <cmath>

/* ==================================================== */
/* GENERAL */

spaceobject::spaceobject(wxPoint pos, int degree) 
	:	position{pos},
		degree{degree}
{}

/* ==================================================== */
/* MOVEMENT */

void spaceobject::move(wxSize size) {
	dx_speed = sin(rad_of(degree));
	dy_speed = -cos(rad_of(degree));
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

/* ==================================================== */
/* POSITION */

void spaceobject::stay_in_universe(wxSize size) {
	if (position.x > size.x) position.x = 0;
	else if (position.x < 0) position.x = size.x;
	else if (position.y > size.y) position.y = 0;
	else if (position.y < 0) position.y = size.y;
}

bool spaceobject::is_in_universe(wxSize size) {
	return position.x <= size.x && position.x >= 0 && position.y <= size.y && position.y >= 0;
}

/* ==================================================== */
/* GETTERS */

wxRealPoint spaceobject::get_position() const {
	return position;
}

int spaceobject::get_degree() const {
	return degree;
}

/* ==================================================== */
/* HELPER FUNCTION */

double spaceobject::rad_of(int deg) {
	return deg * M_PI / 180;
}

