#include "spaceobject.h"
#include <cmath>

spaceobject::spaceobject(wxPoint pos, int degree) 
	:	position{pos},
		degree{degree}
{}


void spaceobject::move(wxSize size) {
	dx_speed = sin(degree * M_PI / 180) * 2;
	dy_speed = -cos(degree * M_PI / 180) * 2;

	std::cout << "dx = " << dx_speed << " | dy = " << dy_speed << std::endl;

	position.x += dx_speed;
	position.y += dy_speed;
}

void spaceobject::decrease_speed() {

}