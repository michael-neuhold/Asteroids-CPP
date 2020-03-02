#include "spaceship.h"

spaceship::spaceship(wxPoint point_start, wxPoint point_end, const wxPen& pen, const wxBrush& brush) 
	: ship{ point_start , point_end },
		pen{pen}, 
		brush{brush} {}

void spaceship::draw(context& con) {
	con.SetPen(pen);
	con.SetBrush(brush);
	con.DrawRectangle(ship);
}

/* ==================================================== */

/* get top-left and bottom-right position of ship */
wxPoint spaceship::get_top_left() const {
	return ship.GetLeftTop();
}

wxPoint spaceship::get_bottom_right() const {
	return ship.GetBottomRight();
}

/* ==================================================== */

/* set new position of ship */
void spaceship::set_new_pos(const wxPoint &top_left, const wxPoint &bottom_right) {
	ship.SetTopLeft(top_left);
	ship.SetBottomRight(bottom_right);
}
