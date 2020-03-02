#pragma once
#include "shapes.h"
#include <ml5/ml5.h>
#include "spaceship.h"

struct draw_application final : ml5::application {
	auto make_window() const->std::unique_ptr<ml5::window> override;

private:
	struct window final : ml5::window {
		window();
	private:

		// some types
		enum class shape_type { rectangle, ellipse, line  };
		shape_type next_shape{ shape_type::line };
		enum class operation { none, moving, dragging };
		operation current_operation{ operation::none };

		// basic functions
		void on_init() override;
		void on_menu(const ml5::menu_event& event);
		auto make_shape(wxPoint pos) const->std::unique_ptr<shape>;
		void on_paint(const ml5::paint_event& event) override;
		
		// asteroids...
		void on_key(ml5::key_event const& event);

		wxPoint last_move_pos;
		wxBrush brush{ *wxGREEN_BRUSH };
		wxPen pen{ *wxBLACK_PEN };
		ml5::vector<std::unique_ptr<shape>> shapes;
		std::unique_ptr<shape> new_shape;
		
		/* left bar */
		std::unique_ptr<shape> left_bar{nullptr};
		ml5::vector<std::unique_ptr<shape>> left_bar_icons;

		/* select tool active */
		bool select_tool_active{false};
		std::unique_ptr<shape> selected_shape;
		ml5::vector<std::unique_ptr<shape>> selection_marker;

		/* cut, copy, paste */
		std::unique_ptr<shape> clipboard_shape{ nullptr };

		/*spaceship*/
		spaceship spaceship{ {10,10},{20,20},*wxBLACK_PEN,*wxGREEN_BRUSH };
	};
};
