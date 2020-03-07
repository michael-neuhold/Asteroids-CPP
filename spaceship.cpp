#include "spaceship.h"
#include <cmath>

spaceship::spaceship(wxPoint pos, int degree)
	:	spaceobject{pos,degree}
{
	wxImage::AddHandler(new wxPNGHandler);
	spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\spaceship_white.png"), wxBITMAP_TYPE_PNG);
	spaceship_image.Rescale(60, 60);
	
	original_spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\spaceship_white.png"), wxBITMAP_TYPE_PNG);
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
/* movements */

void spaceship::rotate_left() {
	degree -= 10;
	if (degree == -10) degree = 350;
}

void spaceship::rotate_right() {
	degree += 10;
	if (degree == 370) degree = 10;
}

void spaceship::boost(wxSize size) {
	dx_speed += sin(degree * M_PI / 180) * 5;
	dy_speed += -cos(degree * M_PI / 180) * 5;
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}
