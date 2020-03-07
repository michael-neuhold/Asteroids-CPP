#pragma once
#include <ml5/ml5.h>
#include "spaceobject.h"

class asteroids : public spaceobject
{
	
public:
	using context = ml5::paint_event::context_t;

	asteroids(wxPoint pos, int radius, int degree);
	~asteroids();

	void draw(context& con);

private:
	int radius;

};

