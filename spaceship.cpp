#include "spaceship.h"
#include <cmath>

constexpr int DEGREE_OFFSET{ 5 };
constexpr int CIRCLE_DEGREE{ 360 };
constexpr int SPACESHIP_SIZE{ 40 };
constexpr int INIT_SPEED{ 2 };
constexpr int BOOST_SPEED{ 5 };

/* GENERAL ============================================ */
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

/* DRAW SPACESHIP ===================================== */
void spaceship::draw(context& con) {
	wxPoint pos{ position };
	spaceship_image.Destroy();
	spaceship_image.CleanUpHandlers();
	spaceship_image = original_spaceship_image.Rotate(-rad_of(degree), pos);
	con.DrawBitmap(spaceship_image, pos);
}

/* ROTATION =========================================== */
void spaceship::rotate_left() {
	if (is_stopped) return;
	degree -= DEGREE_OFFSET;
	if (degree == -DEGREE_OFFSET) degree = CIRCLE_DEGREE - DEGREE_OFFSET;
}

void spaceship::rotate_right() {
	if (is_stopped) return;
	degree += DEGREE_OFFSET;
	if (degree == CIRCLE_DEGREE + DEGREE_OFFSET) degree = DEGREE_OFFSET;
}

/* MOVEMENT =========================================== */
void spaceship::boost(const wxSize &size) {
	if (is_stopped) return;
	dx_speed += sin(rad_of(degree)) * BOOST_SPEED;
	dy_speed += -cos(rad_of(degree)) * BOOST_SPEED;
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
	prev_degree = degree;
}

void spaceship::move(const wxSize &size) {
	if (is_stopped) return;
	dx_speed = sin(rad_of(prev_degree)) * INIT_SPEED;
	dy_speed = -cos(rad_of(prev_degree)) * INIT_SPEED;
	position.x += dx_speed;
	position.y += dy_speed;
	stay_in_universe(size);
}

/* SET CENTER ========================================= */
void spaceship::set_center(const wxSize &size) {
	position.x = (size.x / 2) - (SPACESHIP_SIZE / 2);
	position.y = (size.y / 2) - (SPACESHIP_SIZE / 2);
	degree = 0;
	prev_degree = 0;
	dx_speed = 0;
	dy_speed = 0;
}

/* COLLISION ========================================== */
bool spaceship::crashed(wxRegion asteroid) {
	wxRegion test{ int(position.x),int(position.y),1,1 };
	asteroid.Intersect(test);
	return !asteroid.IsEmpty();
}
