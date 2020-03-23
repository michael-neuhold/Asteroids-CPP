#include "ufo.h"

ufo::ufo(wxRealPoint pos, int degree)
	: spaceobject(pos, degree)
{}

ufo::~ufo() { }

void ufo::draw(context& con) {
	con.SetPen(*wxWHITE_PEN);
	con.SetBrush(*wxBLACK_BRUSH);
	wxRealPoint pos;
	wxPointList point_list;
	wxPoint points_int[11];
	for (int i = 0; i < 11; i++) {
		pos = { point_container[i].x * 2 + position.x, point_container[i].y * 2 + position.y };
		points_int[i] = wxPoint(pos);
		point_list.Append(points_int + i);
	}
	con.DrawPolygon(&point_list);
}

void ufo::move(wxSize size) {
	if (is_stopped) return;
	dx_speed = sin(rad_of(degree));
	dy_speed = -cos(rad_of(degree));
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

/* COLLISION ========================================== */
bool ufo::was_hit(wxRealPoint bullet_pos) {
	wxRegion reg = get_region();
	reg.Intersect(bullet_pos.x, bullet_pos.y, 3, 3);
	return !reg.IsEmpty();
}

wxRegion ufo::get_region() const {
	wxPoint points_int[11];
	wxRealPoint pos;
	for (int i = 0; i < 11; i++) {
		pos = { point_container[i].x * 2 + position.x, point_container[i].y * 2 + position.y };
		points_int[i] = wxPoint(pos);
	};
	return wxRegion{ 11, points_int };
}
