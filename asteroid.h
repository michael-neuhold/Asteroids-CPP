#pragma once
#include <ml5/ml5.h>
#include "spaceobject.h"

class asteroid : public spaceobject
{
	
public:
	using context = ml5::paint_event::context_t;

	asteroid(wxPoint pos, int radius, int degree);
	~asteroid();

	void draw(context& con);

private:
	int radius;

};

