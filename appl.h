#pragma once
#include "shapes.h"
#include <ml5/ml5.h>
#include "spaceship.h"
#include "asteroids.h"

struct draw_application final : ml5::application {
	auto make_window() const->std::unique_ptr<ml5::window> override;

private:
	struct window final : ml5::window {
		window();
	private:

		// basic functions
		void on_init() override;
		void on_menu(const ml5::menu_event& event);
		void on_paint(const ml5::paint_event& event) override;
		void on_timer(const ml5::timer_event& event);
		
		// asteroids...
		void on_key(ml5::key_event const& event);
		bool valid_position(const wxPoint &pos);

		// spaceship
		spaceship spaceship{ {100,100}, 0 };
		asteroids asteroid_test{ { 40 , 40 } , 20, 150 };
		//ml5::vector<asteroids> asteroidsContainer;
		//wxImage asteroid_image;
	};

};
