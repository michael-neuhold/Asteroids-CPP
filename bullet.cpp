#include "bullet.h"

/* ==================================================== */
/* GENERAL */

bullet::bullet(wxPoint pos, int degree) : spaceobject{pos,degree} {
}

/* ==================================================== */
/* DRAW */

void bullet::draw(context& con) {
	con.SetPen(*wxRED_PEN);
	con.SetBrush(*wxRED_BRUSH);
	con.DrawCircle(position,3);
}

/* ==================================================== */
/* MOVEMENT */

void bullet::boost(wxSize size) {
	dx_speed += sin(degree * M_PI / 180) * 5;
	dy_speed += -cos(degree * M_PI / 180) * 5;
	position.x += dx_speed;
	position.y += dy_speed;
	//stay_in_universe(size);
}

