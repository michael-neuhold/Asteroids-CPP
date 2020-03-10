#include "asteroid.h"
#include <cmath>

asteroid::asteroid(wxPoint pos, int radius, int degree)
	:	spaceobject(pos,degree),
		radius{radius}
{
	set_points();
}

asteroid::~asteroid() {
	//nothing to do
}

void asteroid::set_points() {
	int segment = 360 / 8;
	for (int i = 0; i < 8; i++) {
		points[i] = {
			sin(rad_of(segment * i)) * radius + position.x,
			-cos(rad_of(segment * i)) * radius + position.y
		};
	}
}

void asteroid::draw(context& con) {
	con.SetPen(*wxWHITE_PEN);
	con.SetBrush(*wxBLACK_BRUSH);

	//con.DrawCircle(pos, radius);
	
	// draw polygon instead circle
	wxPointList point_list;
	wxPoint points_int[8];
	for (int i = 0; i < 8; i++) {
		points_int[i] = wxPoint(points[i]);
		point_list.Append(points_int + i);
	}
	con.DrawPolygon(&point_list);	
}

void asteroid::move(wxSize size) {
	dx_speed = sin(rad_of(degree)) * 2;		// 5
	dy_speed = -cos(rad_of(degree)) * 2;	// 5
	position.x += dx_speed;
	position.y += dy_speed;
	set_points();
	stay_in_universe(size);
}

/*
bool asteroid::hit(wxPoint bullet_pos) {
	wxPoint points_test[8];
	for (int i = 0; i < 8; i++) {
		points_test[i] = wxPoint(points[i]);
	}
	wxRegion reg{ 8, points_test };

	wxRegion bul{ bullet_pos.x,bullet_pos.y,2,2 };

	std::cout << reg.Contains(bullet_pos);

	return false;// reg.Intersect(bul);

	if ((bullet_pos.x - position.x) * (bullet_pos.x - position.x) +
		(bullet_pos.y - position.y) * (bullet_pos.y - position.y) - degree * degree)
		return true;
	else
		return false;

}
*/