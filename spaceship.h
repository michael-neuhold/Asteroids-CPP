#pragma once
#include <ml5/ml5.h>
#include "spaceobject.h"
#include <wx/sound.h>

class spaceship : public spaceobject
{
	
public:
	using context = ml5::paint_event::context_t;
	spaceship(wxPoint pos, int degree, bool with_boost);
	~spaceship();

	void draw(context& con);
	void rotate_left();
	void rotate_right();
	void set_center(wxSize size);
	void move(wxSize size) override;
	void boost(wxSize size);
	bool crashed(wxRegion asteroid);

private:

	wxImage original_spaceship_image;
	wxImage spaceship_image;
	int prev_degree;			// for holding direction (drifting)

};

