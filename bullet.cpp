#include "bullet.h"

constexpr int INIT_SPEED{ 5 };

/* GENERAL ============================================ */
bullet::bullet(wxPoint pos, int degree) 
  : spaceobject{pos,degree} 
{}

/* DRAW =============================================== */
void bullet::draw(context& con) {
	con.SetPen(*wxRED_PEN);
	con.SetBrush(*wxRED_BRUSH);
	con.DrawCircle(position,3);
}

/* MOVEMENT =========================================== */
void bullet::move(const wxSize &size) {
	if (is_stopped) return;
	dx_speed += sin(degree * M_PI / 180) * INIT_SPEED;
	dy_speed += -cos(degree * M_PI / 180) * INIT_SPEED;
	position.x += dx_speed;
	position.y += dy_speed;
}

