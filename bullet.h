#pragma once
#include "spaceobject.h"

class bullet : public spaceobject {

	using context = ml5::paint_event::context_t;

public:
	bullet(wxPoint pos, int degree);
	void draw(context& con);
	void move(wxSize size);

};