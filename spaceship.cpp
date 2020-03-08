#include "spaceship.h"
#include <cmath>

#define DEGREE_OFFSET 5

spaceship::spaceship(wxPoint pos, int degree)
	:	spaceobject{pos,degree}
{
	wxImage::AddHandler(new wxPNGHandler);
	spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\spaceship_white.png"), wxBITMAP_TYPE_PNG);
	spaceship_image.Rescale(spaceship_size, spaceship_size);
	
	original_spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\spaceship_white.png"), wxBITMAP_TYPE_PNG);
	original_spaceship_image.Rescale(spaceship_size, spaceship_size);
}

spaceship::~spaceship() {
	wxImage::CleanUpHandlers();
}

void spaceship::draw(context& con) {
	spaceship_image.CleanUpHandlers();
	spaceship_image = original_spaceship_image.Rotate(-rad_of(degree), position);
	con.DrawBitmap(spaceship_image, position);
}

/* ==================================================== */
/* movements */

void spaceship::rotate_left() {
	degree -= DEGREE_OFFSET;
	if (degree == -DEGREE_OFFSET) degree = 360 - DEGREE_OFFSET;
}

void spaceship::rotate_right() {
	degree += DEGREE_OFFSET;
	if (degree == 360 + DEGREE_OFFSET) degree = DEGREE_OFFSET;
}

void spaceship::boost(wxSize size) {
	dx_speed += sin(rad_of(degree)) * 5;
	dy_speed += -cos(rad_of(degree)) * 5;
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

void spaceship::set_center(wxSize size) {
	position.x = (size.x / 2) - spaceship_size;
	position.y = size.y - 40;
}
