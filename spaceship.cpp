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

void spaceship::boost(/*wxSize size*/) {
	
	dx_speed += sin(degree * M_PI / 180) * 5;
	dy_speed += -cos(degree * M_PI / 180) * 5;

	//std::cout << "dx = " << dx << " | dy = " << dy << std::endl;

	position.x += dx_speed;
	position.y += dy_speed;

	/*
	if (position.x >= size.x) position.x = 0;
	else if (position.x == 0) position.x = size.x;
	else if (position.y >= size.y) position.y = 0;
	else if (position.y == 0) position.y = size.y;
	*/
}
