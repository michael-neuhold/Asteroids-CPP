#include "spaceship.h"
#include <cmath>

spaceship::spaceship() {
	
	wxImage::AddHandler(new wxPNGHandler);
	spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\spaceship.png"), wxBITMAP_TYPE_PNG);
	spaceship_image.Rescale(60, 60);
	
	original_spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\spaceship.png"), wxBITMAP_TYPE_PNG);
	original_spaceship_image.Rescale(60, 60);

}

spaceship::~spaceship() {
	wxImage::CleanUpHandlers();
}

void spaceship::draw(context& con) {
	spaceship_image.CleanUpHandlers();
	spaceship_image = original_spaceship_image.Rotate(-degree*(M_PI/180), position);
	std::cout << "rad: " << degree * (M_PI / 180) << std::endl;
	con.DrawBitmap(spaceship_image, position);
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

/* ==================================================== */
/* movements */

void spaceship::rotate_left() {
	if (degree - 10 == -10) {
		degree = 350;
		return;
	}
	degree -= 10;
	std::cout << "rotate left" << "current degree: " << degree << std::endl;
}

void spaceship::rotate_right() {
	if (degree + 10 == 370) {
		degree = 10;
		return;
	}
	degree += 10;
	std::cout << "rotate right" << "current degree: " << degree << std::endl;
}

void spaceship::boost(wxSize size) {
	std::cout << "boost" << "current degree: " << degree << " __ ";

	dx = sin(degree * M_PI / 180) * 2;
	dy = -cos(degree * M_PI / 180) * 2;

	std::cout << "dx = " << dx << " | dy = " << dy << std::endl;

	position.x += dx;
	position.y += dy;

	if (position.x >= size.x) position.x = 0;
	else if (position.x == 0) position.x = size.x;
	else if (position.y >= size.y) position.y = 0;
	else if (position.y == 0) position.y = size.y;

}
