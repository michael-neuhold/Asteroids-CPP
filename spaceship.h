#pragma once
#include <ml5/ml5.h>

class spaceship : public ml5::object
{
	
public:
	using context = ml5::paint_event::context_t;
	spaceship(wxPoint point_start, wxPoint point_end, const wxPen& pen, const wxBrush& brush);
	~spaceship();

	wxPoint get_top_left() const;
	wxPoint get_bottom_right() const;

	void set_new_pos(const wxPoint& top_left, const wxPoint& bottom_right);
	void draw(context& con);

private:
	wxRect ship;
	wxPen pen;
	wxBrush brush;
};

