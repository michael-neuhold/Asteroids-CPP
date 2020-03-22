#include "spaceship.h"
#include <cmath>

#define DEGREE_OFFSET 5
#define CIRCLE_DEGREE 360
#define SPACESHIP_SIZE 40

/* ==================================================== */
/* GENERAL */

spaceship::spaceship(wxPoint pos, int degree, bool with_boost)
	: spaceobject{ pos,degree },
	prev_degree{ degree }
{
	std::string image_name;
	if (with_boost) image_name = "spaceship_boost.png";
	else image_name = "spaceship_white.png";

	wxImage::AddHandler(new wxPNGHandler);
	spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\" + image_name), wxBITMAP_TYPE_PNG);
	spaceship_image.Rescale(SPACESHIP_SIZE, SPACESHIP_SIZE);

	original_spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\" + image_name), wxBITMAP_TYPE_PNG);
	original_spaceship_image.Rescale(SPACESHIP_SIZE, SPACESHIP_SIZE);
}

spaceship::~spaceship() {
	wxImage::CleanUpHandlers();
}

/* ==================================================== */
/* DRAW SPACESHIP */

void spaceship::draw(context& con) {
	wxPoint pos{ position };
	spaceship_image.CleanUpHandlers();
	spaceship_image = original_spaceship_image.Rotate(-rad_of(degree), pos);
	con.DrawBitmap(spaceship_image, pos);
}

/* ==================================================== */
/* ROTATION */

void spaceship::rotate_left() {
	degree -= DEGREE_OFFSET;
	if (degree == -DEGREE_OFFSET) degree = CIRCLE_DEGREE - DEGREE_OFFSET;
}

void spaceship::rotate_right() {
	degree += DEGREE_OFFSET;
	if (degree == CIRCLE_DEGREE + DEGREE_OFFSET) degree = DEGREE_OFFSET;
}

/* ==================================================== */
/* MOVEMENT */

void spaceship::boost(wxSize size) {
	dx_speed += sin(rad_of(degree)) * 5;
	dy_speed += -cos(rad_of(degree)) * 5;
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
	prev_degree = degree;
}

void spaceship::move(wxSize size) {
	if (stop) return;
	dx_speed = sin(rad_of(prev_degree)) * 2;
	dy_speed = -cos(rad_of(prev_degree)) * 2;
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

/* ==================================================== */
/* SET CENTER */

void spaceship::set_center(wxSize size) {
	position.x = (size.x / 2) - (SPACESHIP_SIZE / 2);
	position.y = (size.y / 2) - (SPACESHIP_SIZE / 2);
	degree = 0;
	prev_degree = 0;
	dx_speed = 0;
	dy_speed = 0;
}

/* ==================================================== */
/* COLLISION */

bool spaceship::crashed(wxRegion asteroid) {
	wxRegion test{ int(position.x),int(position.y),1,1 };
	asteroid.Intersect(test);
	return !asteroid.IsEmpty();
}

/* ==================================================== */
/* END */

void spaceship::stop_spaceship() {
	stop = true;
}