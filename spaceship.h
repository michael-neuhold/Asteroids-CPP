#pragma once
#include <ml5/ml5.h>

class spaceship : public ml5::object
{
	
public:
	using context = ml5::paint_event::context_t;
	spaceship();
	~spaceship();

	wxPoint get_top_left() const;
	wxPoint get_bottom_right() const;

	void set_new_pos(const wxPoint& top_left, const wxPoint& bottom_right);
	void draw(context& con);

	/* movements */
	void rotate_left();
	void rotate_right();
	void boost(wxSize size);

private:
	wxRect ship;
	wxPen pen;
	wxBrush brush;

	/* spaceship image */
	wxImage original_spaceship_image;
	wxImage spaceship_image;
	wxPoint position{ {100,100} };
	double degree = 0;

	float dx = 0;
	float dy = 0;
};

