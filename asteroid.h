#pragma once
#include <ml5/ml5.h>
#include "spaceobject.h"

class asteroid : public spaceobject
{
	
public:
	using context = ml5::paint_event::context_t;

	asteroid(wxPoint pos, int radius, int degree);
	~asteroid();

	void move(wxSize size) override;
	void draw(context& con);
	void set_points();
	bool was_hit(wxPoint bullet_pos);
	wxRegion get_region() const;
	int get_radius() const;

private:
	int radius;
	wxRealPoint points[8];

};

