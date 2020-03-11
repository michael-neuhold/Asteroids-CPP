#include "appl.h"
#define INTERVAL 10000000
#define RAND_RADIUS rand() % 40
#define RAND_DEGREE rand() % 360
#define INITIAL_ASTEROIDS 5

/* ==================================================== */
/* GENERAL */

//draw_application
auto draw_application::make_window() const->std::unique_ptr<ml5::window> { 
	return std::make_unique<window>();
}

//window
draw_application::window::window() : ml5::window{"ML5.Asteroids"} {	}

/* ==================================================== */
/* INIT */

void draw_application::window::on_init() {
	set_prop_background_brush(*wxBLACK_BRUSH);
	ml5::duration_t time(INTERVAL);
	start_timer(time);
	create_asteroids_rand(INITIAL_ASTEROIDS);
	spaceship.set_center(get_size());
}

/* ==================================================== */
/* CALL DRAW FUNCTIONS */

void draw_application::window::on_paint(const ml5::paint_event& event) {
	auto& con{ event.get_context() };
	for (auto& a : asteroid_container) a->draw(con);
	for (auto& b : bullet_container) b->draw(con);
	spaceship.draw(con);
	status.draw(con);
	set_status_text("HIT COUNT: " + std::to_string(status.get_hit_counter()));
}

/* ==================================================== */
/* REACT ON KEY EVENT */

void draw_application::window::on_key(ml5::key_event const& event) {
	wxPoint bullet_position;
	switch (event.get_key_code())
	{
	case 32: //SHOOT
		bullet_position = { wxPoint(spaceship.get_position()).x + 20 , wxPoint(spaceship.get_position()).y + 20 };
		bullet_container.add(std::make_unique<bullet>(bullet_position, spaceship.get_degree()));
		wxSound (R"(C:\Users\michaelneuhold\Desktop\fire.wav)").Play();
		break;
	case 314:	spaceship.rotate_left(); 		break;		//LEFT
	case 315:	spaceship.boost(get_size());	break;		//UP
	case 316:	spaceship.rotate_right();		break;		//RIGHT
	default:	std::cout << "wrong key..." << std::endl;
	}

	refresh();
}

/* ==================================================== */
/* CREATE NEW ASTEROIDS */

void draw_application::window::create_asteroids_rand(int cnt) {
	wxPoint asteroid_position;
	for (int i = 0; i < cnt; i++) {
		asteroid_position = { rand() % get_size().x,rand() % get_size().y };
		asteroid_container.add(std::make_unique<asteroid>(wxPoint(asteroid_position), RAND_RADIUS, RAND_DEGREE));
	}
}

void draw_application::window::create_asteroids(wxRealPoint asteroid_position, int radius, int cnt) {
	for (int i = 0; i < cnt; i++) {
		asteroid_container.add(std::make_unique<asteroid>(wxPoint(asteroid_position), radius, RAND_DEGREE));
	}
}

/* ==================================================== */
/* COLLISIONS */

void draw_application::window::collision_detection() {
	wxRealPoint new_asteroid_pos;
	int new_asteroid_radius;
	for (auto& b : bullet_container) {
		wxPoint pos{ b->get_position() };
		std::unique_ptr<asteroid>* to_delete{nullptr};
		for (auto& a : asteroid_container) {
			if (a->was_hit(pos)) {
				to_delete = &a;
				new_asteroid_pos = a->get_position();
				new_asteroid_radius = a->get_radius();
				status.increase_hit_counter();
			}
		}

		if (to_delete) {
			if (new_asteroid_radius >= 20) {
				create_asteroids(new_asteroid_pos, new_asteroid_radius / 2, 2);
			}
			asteroid_container.remove(*to_delete);
		}
	}

	for (auto& b : asteroid_container) {
		if (spaceship.crashed(b->get_region())) {
			spaceship.set_center(get_size());
			status.decrease_life_counter();
			if (status.get_life_counter() == 0) {
				spaceship.set_center(get_size());
				spaceship.stop_spaceship();
			}
		}
	}
	
}

/* ==================================================== */
/* UPDATE GAME STATE */

void draw_application::window::on_timer(const ml5::timer_event& event) {
	create_asteroids_rand(INITIAL_ASTEROIDS - asteroid_container.size());
	for (auto &a : asteroid_container) a->move(get_size());
	for (auto &b : bullet_container) b->boost(get_size());
	collision_detection();
	spaceship.move(get_size());
	refresh();
}
