#pragma once

#include <ml5/ml5.h>
#include "spaceobject.h"

class ufo : public spaceobject {

public:
	using context = ml5::paint_event::context_t;

	ufo(wxRealPoint pos, int degree);
	~ufo();

	void move(wxSize size) override;
	void draw(context& con);
	bool was_hit(wxRealPoint bullet_pos);
	wxRegion get_region() const;

private:
	wxRealPoint point_container[11] = { 
			{ -10,8.5 }, { -6,8 }, { -2,7.5 }, 
			{ -1,5 }, { 0,4.5 }, { 1,5 }, 
			{ 2,7.5 }, { 6,8 }, { 10,8.5 }, 
			{ 6,12 }, { -6,12 } 
	};
};