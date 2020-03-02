#include "appl.h"


//draw_application
auto draw_application::make_window() const->std::unique_ptr<ml5::window> { 
	return std::make_unique<window>(); 
}

//window
draw_application::window::window() : ml5::window{"ML5.Asteroids"} {
	// init spaceship .png image
	wxImage::AddHandler(new wxPNGHandler);
	asteroid_image.LoadFile(wxT("C:\\Users\\michaelneuhold\\Desktop\\spaceship.png"), wxBITMAP_TYPE_PNG);
	asteroid_image.Rescale(60,60);
}


void draw_application::window::on_key(ml5::key_event const& event) {
	
	wxPoint top_left		= spaceship.get_top_left();
	wxPoint bottom_right	= spaceship.get_bottom_right();

	wxPoint new_top_left, new_bottom_right;
	
	int offset = 5;

	std::cout << "key code: " << event.get_key_code() << std::endl;

	switch (event.get_key_code())
	{
	
	case 114: //ROTATE
		
		break;
	case 314: //LEFT
		new_top_left		= { top_left.x - offset , top_left.y };
		new_bottom_right	= { bottom_right.x - offset , bottom_right.y };
		if (valid_position(new_top_left) && valid_position(new_bottom_right))
			spaceship.set_new_pos(new_top_left, new_bottom_right);
		break;
	case 315: //UP
		new_top_left		= { top_left.x , top_left.y - offset };
		new_bottom_right	= { bottom_right.x , bottom_right.y - offset };
		if (valid_position(new_top_left) && valid_position(new_bottom_right))
			spaceship.set_new_pos(new_top_left, new_bottom_right);
		break;
	case 316: //RIGHT
		new_top_left		= { top_left.x + offset , top_left.y };
		new_bottom_right	= { bottom_right.x + offset , bottom_right.y };
		if (valid_position(new_top_left) && valid_position(new_bottom_right))
			spaceship.set_new_pos(new_top_left, new_bottom_right);
		break;
	case 317: //DOWN
		new_top_left		= { top_left.x , top_left.y + offset };
		new_bottom_right	= { bottom_right.x , bottom_right.y + offset };
		if (valid_position(new_top_left) && valid_position(new_bottom_right))
			spaceship.set_new_pos(new_top_left, new_bottom_right);
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

	// rotate image with given angle and center
	asteroid_image = asteroid_image.Rotate(45, {20,20});

	con.DrawBitmap(asteroid_image, { 40 , 40 });

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
	set_prop_background_brush(*wxGREY_BRUSH);
}
