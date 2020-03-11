#pragma once
#include "shapes.h"
#include <ml5/ml5.h>
#include "spaceship.h"
#include "asteroid.h"
#include "bullet.h"
#include "game_status.h"

struct draw_application final : ml5::application {
	auto make_window() const->std::unique_ptr<ml5::window> override;

private:
	struct window final : ml5::window {
		window();
	private:

		// event handler
		void on_init() override;
		//void on_menu(const ml5::menu_event& event) override;
		void on_paint(const ml5::paint_event& event) override;
		void on_timer(const ml5::timer_event& event) override;
		void on_key(ml5::key_event const& event) override;
		void create_asteroids_at(wxRealPoint asteroid_position, int radius, int cnt);

		// space objects
		void collision_detection();

		

		// spaceship
		spaceship spaceship{ {100,100}, 0, true };
		ml5::vector<std::unique_ptr<asteroid>>	asteroid_container;
		ml5::vector<std::unique_ptr<bullet>>	bullet_container;
		
		// game status
		game_status status{3};

	};

};
