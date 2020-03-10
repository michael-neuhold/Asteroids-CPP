#include "spaceship.h"
#include <cmath>

#define DEGREE_OFFSET 5

spaceship::spaceship(wxPoint pos, int degree, bool with_boost)
	:	spaceobject{pos,degree},
		prev_degree{degree}
{
	std::string image_name;
	if (with_boost) image_name = "spaceship_boost.png";
	else image_name = "spaceship_white.png";

	wxImage::AddHandler(new wxPNGHandler);
	spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\" + image_name), wxBITMAP_TYPE_PNG);
	spaceship_image.Rescale(spaceship_size, spaceship_size);
	
	original_spaceship_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\" + image_name), wxBITMAP_TYPE_PNG);
	original_spaceship_image.Rescale(spaceship_size, spaceship_size);
}

spaceship::~spaceship() {
	wxImage::CleanUpHandlers();
}

void spaceship::draw(context& con) {
	wxPoint pos{ position };
	spaceship_image.CleanUpHandlers();
	spaceship_image = original_spaceship_image.Rotate(-rad_of(degree), pos);
	con.DrawBitmap(spaceship_image, pos);
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
	prev_degree = degree;
}

void spaceship::set_center(wxSize size) {
	position.x = (size.x / 2) - spaceship_size;
	position.y = size.y / 2;
	degree = 0;
	dx_speed = 0;
	dy_speed = 0;
}

void spaceship::move(wxSize size) {
	if (stop) return;
	dx_speed = sin(rad_of(prev_degree));
	dy_speed = -cos(rad_of(prev_degree));
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

bool spaceship::crashed(wxRegion asteroid) {
	//wxBitmap spaceship_bitmap{spaceship_image};
	//wxRegion image_region{ wxBitmap(spaceship_image) };
	wxRegion test{int(position.x),int(position.y),2,2};
	//std::cout << "x = " << asteroid.GetBox().x << " y = " << asteroid.GetBox().y << std::endl;
	asteroid.Intersect(test);
	return !asteroid.IsEmpty();
}

void spaceship::stop_spaceship() {
	stop = true;
}