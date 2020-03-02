#include "appl.h"

//draw_application
auto draw_application::make_window() const->std::unique_ptr<ml5::window> { 
	return std::make_unique<window>(); 
}

//window
draw_application::window::window() : ml5::window{"ML5.Asteroids"} {}



/* ============= make shapes ============ */

auto draw_application::window::make_shape(wxPoint pos) const -> std::unique_ptr<shape> {
	switch (next_shape) {
		case shape_type::line: return std::make_unique<line>(pos, pen, brush); break;
		case shape_type::ellipse: return std::make_unique<ellipse>(pos, pen, brush); break;
		case shape_type::rectangle: return std::make_unique<rectangle>(pos, pen, brush); break;
		default: throw std::logic_error{ "unknown shape type" };
	}
}

void draw_application::window::on_key(ml5::key_event const& event) {
	
	wxPoint top_left		= spaceship.get_top_left();
	wxPoint bottom_right	= spaceship.get_bottom_right();

	wxPoint new_top_left, new_bottom_right;
	
	int offset = 5;

	switch (event.get_key_code())
	{
	case 314: //LEFT
		new_top_left		= { top_left.x - offset , top_left.y };
		new_bottom_right	= { bottom_right.x - offset , bottom_right.y };
		spaceship.set_new_pos(new_top_left,new_bottom_right);
		break;
	case 315: //UP
		new_top_left		= { top_left.x , top_left.y - offset };
		new_bottom_right	= { bottom_right.x , bottom_right.y - offset };
		spaceship.set_new_pos(new_top_left, new_bottom_right);
		break;
	case 316: //RIGHT
		new_top_left		= { top_left.x + offset , top_left.y };
		new_bottom_right	= { bottom_right.x + offset , bottom_right.y };
		spaceship.set_new_pos(new_top_left, new_bottom_right);
		break;
	case 317: //DOWN
		new_top_left		= { top_left.x , top_left.y + offset };
		new_bottom_right	= { bottom_right.x , bottom_right.y + offset };
		spaceship.set_new_pos(new_top_left, new_bottom_right);
		break;
	default:
		std::cout << "wrong key..." << std::endl;
		break;
	}
		
	refresh();
}

void draw_application::window::on_paint(const ml5::paint_event &event) {
	/*
	auto& con{ event.get_context() };
	// draw shapes on board
	for (const auto& s : shapes) s->draw(con);
	// draw current shape
	if (new_shape) new_shape->draw(con);
	// draw left-nav-bar
	if (left_bar) left_bar->draw(con);
	for (const auto &s : left_bar_icons) s->draw(con);
	// draw selection marker
	for (const auto& s : selection_marker) s->draw(con);
	// draw selected shape
	if (selected_shape) selected_shape->draw(con);
	*/
	auto& con{ event.get_context() };
	spaceship.draw(con);
}


void draw_application::window::on_menu(const ml5::menu_event& event) {

	const auto item{ event.get_title_and_item() };
	if (item == "Shape/Rectangle") {
		next_shape = shape_type::rectangle;
	
	}
	else if (item == "Shape/Ellipse") {
		next_shape = shape_type::ellipse;
		
	}
	else if (item == "Shape/Line") {
		next_shape = shape_type::line;
	
	}

	if (item == "Brush/Blue")				brush = *wxBLUE_BRUSH;
	else if (item == "Brush/Green")			brush = *wxGREEN_BRUSH;
	else if (item == "Brush/Red")			brush = *wxRED_BRUSH;
	else if (item == "Brush/White")			brush = *wxWHITE_BRUSH;
	else if (item == "Brush/Light Gray")	brush = *wxLIGHT_GREY_BRUSH;
	else if (item == "Brush/Black")			brush = *wxBLACK_BRUSH;

	if (item == "Pen/Blue")			pen = *wxBLUE_PEN;
	else if (item == "Pen/Green")	pen = *wxGREEN_PEN;
	else if (item == "Pen/Red")		pen = *wxRED_PEN;
	else if (item == "Pen/White")	pen = *wxWHITE_PEN;
	else if (item == "Pen/Black")	pen = *wxBLACK_PEN;

	if (item == "Background/Blue")				set_prop_background_brush(*wxBLUE_BRUSH);
	else if (item == "Background/Green")		set_prop_background_brush(*wxGREEN_BRUSH);
	else if (item == "Background/Red")			set_prop_background_brush(*wxRED_BRUSH);
	else if (item == "Background/White")		set_prop_background_brush(*wxWHITE_BRUSH);
	else if (item == "Background/Light Gray")	set_prop_background_brush(*wxLIGHT_GREY_BRUSH);
	else if (item == "Background/Black")		set_prop_background_brush(*wxBLACK_BRUSH);

	

	refresh();
}

void draw_application::window::on_init() {
	add_menu("&Shape", {
		{ "&Line"		, "<< next shape: line >>"		},
		{ "&Ellipse"	, "<< next shape: ellipse >>"	},
		{ "&Rectangle"	, "<< next shape: rectangle >>" }
		});

	add_menu("&Brush", {
		{ "&Blue"		, "<< next brush: blue >>"		},
		{ "&Green"		, "<< next brush: green >>"		},
		{ "&Red"		, "<< next brush: red >>"		},
		{ "&White"		, "<< next brush: white >>"		},
		{ "&Light Gray"	, "<< next brush: light gray >>"},
		{ "Blac&k"		, "<< next brush: black >>"		}
		});

	add_menu("&Pen", {
		{ "&Blue"		, "<< next pen: blue >>"		},
		{ "&Green"		, "<< next pen: green >>"		},
		{ "&Red"		, "<< next pen: red >>"			},
		{ "&White"		, "<< next pen: white >>"		},
		{ "Blac&k"		, "<< next pen: black >>"		}
		});

	add_menu("Back&ground", {
		{ "&Blue"		, "<< next background blue >>"			},
		{ "&Green"		, "<< next background green >>"			},
		{ "&Red"		, "<< next background red >>"			},
		{ "&White"		, "<< next background white >>"			},
		{ "&Light Gray"	, "<< next background light gray >>"	},
		{ "Blac&k"		, "<< next background black >>"			}
		});

	add_menu("&Edit", {
		{ "C&ut"	, "<< cut selected shape >>"			},
		{ "&Copy"	, "<< copy selected shape >>"			},
		{ "&Paste"	, "<< paste shape from clipboard >>"	},
		{ "&Select"	, "<< select shape >>"					}
		});

	set_status_text("Use the mouse to draw a shape");

	// init spaceship

}


