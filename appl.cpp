#include "appl.h"

//draw_application
auto draw_application::make_window() const->std::unique_ptr<ml5::window> { 
	return std::make_unique<window>(); 
}

//window
draw_application::window::window() : ml5::window{"ML5.Asteroids"} {
	for (int i = 0; i < 10; i++) {
		//asteroids stone{ {rand()%100,rand()%100} , rand() % 20 };
		//asteroidsContainer.add({ {rand() % 100,rand() % 100} , rand() % 20 });
	}
	
}


void draw_application::window::on_key(ml5::key_event const& event) {

	

	std::cout << "key code: " << event.get_key_code() << std::endl;
	switch (event.get_key_code())
	{
	
	case 32: //shoot
		bullet * new_bullet;
		new_bullet = new bullet{ {spaceship.get_position().x + 30, spaceship.get_position().y + 30 },spaceship.get_degree() };
		bulletContainer.add(new_bullet);
		break;
	case 314: //LEFT
		spaceship.rotate_left();
		break;
	case 315: //UP
		spaceship.boost(get_size());
		break;
	case 316: //RIGHT
		spaceship.rotate_right();
		break;
	case 317: //DOWN
		std::cout << "nothing to do..." << std::endl;
		break;
	default:
		std::cout << "wrong key..." << std::endl;
		//return;
	}

	refresh();
}

void draw_application::window::on_paint(const ml5::paint_event &event) {

	// get context to draw
	auto& con{ event.get_context() };
	spaceship.draw(con);
	asteroid_test.draw(con);
	for (auto &p : asteroidsContainer) {
		p->draw(con);
	}
	for (auto &b : bulletContainer) {
		b->draw(con);
	}

}

bool draw_application::window::valid_position(const wxPoint& pos) {
	return pos.y >= 0 && pos.y <= get_size().y;
}

void draw_application::window::on_menu(const ml5::menu_event& event) {
	std::string title = event.get_item();
	if (title == "Pause") {
		std::cout << "<< Pause >>" << std::endl;
	} else if (title == "Reset") {
		std::cout << "<< Reset >>" << std::endl;
	} else if (title == "Quit") {
		std::cout << "<< Quit >>" << std::endl;
	}
	refresh();
}

void draw_application::window::on_init() {
	add_menu("&Game", {
		{ "&Pause"		, "<< pause game >>"	},
		{ "&Restart"	, "<< restart game >>"	},
		{ "&Quit"		, "<< quit game >>"		}
		});
	set_status_text("use arrow keys to navigate the spaceship");
	set_prop_background_brush(*wxBLACK_BRUSH);
	
	/* setup timer */
	ml5::duration_t time(10000000);
	start_timer(time);

	/* setup default asteroids */
	asteroids* new_stone;
	for (int i = 0; i < 10; i++) {
		new_stone = new asteroids({ rand() % get_size().x,rand() % get_size().y }, rand() % 20, rand() % 360);
		asteroidsContainer.add(new_stone);
	}

}

void draw_application::window::on_timer(const ml5::timer_event& event) {
	asteroid_test.move(get_size());
	for (auto &a : asteroidsContainer) {
		a->move(get_size());
	}
	for (auto &b : bulletContainer) {
		b->boost(get_size());
	}
	
	spaceship.move(get_size());
	refresh();
}
