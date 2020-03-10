#include "appl.h"
#define INTERVAL 10000000
#define RAND_RADIUS rand() % 40
#define RAND_DEGREE rand() % 360
#define INITIAL_ASTEROIDS 5

//draw_application
auto draw_application::make_window() const->std::unique_ptr<ml5::window> { 
	return std::make_unique<window>();
}

//window
draw_application::window::window() : ml5::window{"ML5.Asteroids"} {	
}

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

void draw_application::window::on_paint(const ml5::paint_event &event) {
	auto& con{ event.get_context() };

	for (auto &a : asteroid_container) a->draw(con);
	for (auto &b : bullet_container) b->draw(con);
	spaceship.draw(con);
	status.draw(con);
}

void draw_application::window::on_menu(const ml5::menu_event& event) {
	std::string title = event.get_item();
	if (title == "Pause")		{ std::cout << "<< Pause >>" << std::endl; }
	else if (title == "Reset")	{ std::cout << "<< Reset >>" << std::endl; }
	else if (title == "Quit")	{ std::cout << "<< Quit >>" << std::endl; on_exit(); }
	refresh();
}

void draw_application::window::on_init() {

	/* setup window options */
	add_menu("&Game", {
		{ "&Pause"		, "<< pause game >>"	},
		{ "&Restart"	, "<< restart game >>"	},
		{ "&Quit"		, "<< quit game >>"		}
		});
	set_status_text("hits: " + std::to_string(status.get_hit_counter()));
	set_prop_background_brush(*wxBLACK_BRUSH);
	
	/* setup timer */
	ml5::duration_t time(INTERVAL);
	start_timer(time);

	/* setup asteroids */
	wxPoint asteroid_position;
	for (int i = 0; i < INITIAL_ASTEROIDS; i++) {
		asteroid_position = { rand() % get_size().x,rand() % get_size().y };
		asteroid_container.add(std::make_unique<asteroid>(asteroid_position, RAND_RADIUS, RAND_DEGREE));
	}

	/* setup spaceship */
	spaceship.set_center(get_size());
	
}

void draw_application::window::collision_detection() {
	for (auto& b : bullet_container) {
		wxPoint pos{ b->get_position() };
		std::unique_ptr<asteroid>* to_delete{nullptr};
		for (auto& a : asteroid_container) {
			if (a->was_hit(pos)) to_delete = &a;
		}
		if (to_delete) asteroid_container.remove(*to_delete);
	}

	for (auto& b : asteroid_container) {
		if (spaceship.crashed(b->get_region())) {
			spaceship.set_center(get_size());
			status.decrease_life_counter();
			if (status.get_life_counter() == 0) {
				std::cout << "game over" << std::endl;
				spaceship.set_center(get_size());
				spaceship.stop_spaceship();
			}
		}
	}
}

void draw_application::window::on_timer(const ml5::timer_event& event) {
	for (auto &a : asteroid_container) a->move(get_size());
	for (auto &b : bullet_container) b->boost(get_size());
	collision_detection();
	spaceship.move(get_size());
	set_status_text("hits: " + std::to_string(status.get_hit_counter()));
	refresh();
}
