#include "asteroid.h"
#include <cmath>

asteroid::asteroid(wxPoint pos, int radius, int degree)
	:	spaceobject(pos,degree),
		radius{radius}
{}

asteroid::~asteroid() {
	//nothing to do
}

void asteroid::draw(context& con) {
	con.SetPen(*wxWHITE_PEN);
	con.SetBrush(*wxBLACK_BRUSH);
	con.DrawCircle(position, radius);
}


/*
void asteroids::move(wxSize size) {
	dx_speed = sin(degree * M_PI / 180) * 2;
	dy_speed = -cos(degree * M_PI / 180) * 2;

	std::cout << "dx = " << dx_speed << " | dy = " << dy_speed << std::endl;

	position.x += dx_speed;
	position.y += dy_speed;
}*/