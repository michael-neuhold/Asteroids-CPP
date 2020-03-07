#pragma once
#include <ml5/ml5.h>
#include "spaceobject.h"

class spaceship : public spaceobject
{
	
public:
	using context = ml5::paint_event::context_t;
	spaceship(wxPoint pos, int degree);
	~spaceship();

	void draw(context& con);

	/* movements */
	void rotate_left();
	void rotate_right();
	//void boost(wxSize size);
	//void move(wxSize size) override;
	void boost(wxSize size);

private:

	/* spaceship image */
	wxImage original_spaceship_image;
	wxImage spaceship_image;

};

