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
