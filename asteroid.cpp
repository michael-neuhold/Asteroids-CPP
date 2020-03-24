#include "asteroid.h"
#include <cmath>

constexpr int CORNER_CNT{ 8 };
constexpr int CIRCLE_DEGREE{ 360 };

/* GENERAL ============================================ */
asteroid::asteroid(wxPoint pos, int radius, int degree)
  :	spaceobject(pos,degree), 
	radius{radius},
	speed_factor{ rand() % 3 + 1}
{
	set_points();
}

asteroid::~asteroid() {}

/* SET CORNERS ======================================== */
void asteroid::set_points() {
	int segment = CIRCLE_DEGREE / CORNER_CNT;
	for (int i = 0; i < CORNER_CNT; i++) {
		points[i] = {
			sin(rad_of(segment * i)) * radius + position.x,
			-cos(rad_of(segment * i)) * radius + position.y
		};
	}
}

/* DRAW =============================================== */
void asteroid::draw(context& con) {
	con.SetPen(*wxWHITE_PEN);
	con.SetBrush(*wxBLACK_BRUSH);
	wxPointList point_list;
	wxPoint points_int[8];
	for (int i = 0; i < 8; i++) {
		points_int[i] = wxPoint(points[i]);
		point_list.Append(points_int + i);
	}
	con.DrawPolygon(&point_list);	
}

/* MOVEMENT =========================================== */
void asteroid::move(const wxSize &size) {
	if (is_stopped) return;
	dx_speed = sin(rad_of(degree)) * speed_factor;		
	dy_speed = -cos(rad_of(degree)) * speed_factor;
	position.x += dx_speed;
	position.y += dy_speed;
	set_points();
	stay_in_universe(size);
}

/* COLLISION ========================================== */
bool asteroid::was_hit(const wxRealPoint &bullet_pos) {
	wxRegion reg = get_region(); 
	reg.Intersect(bullet_pos.x, bullet_pos.y, 3, 3);
	return !reg.IsEmpty();
}

/* GETTER ============================================= */
wxRegion asteroid::get_region() const {
	wxPoint points_int[8];
	for (int i = 0; i < 8; i++) points_int[i] = wxPoint(points[i]);
	return wxRegion{ 8, points_int };
}

int asteroid::get_radius() const {
	return radius;
}