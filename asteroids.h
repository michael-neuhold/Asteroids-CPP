#pragma once
#include <ml5/ml5.h>

class asteroids : public ml5::object 
{
	
public:
	using context = ml5::paint_event::context_t;

	asteroids(wxPoint pos, int radius);
	~asteroids();

	void draw(context& con);
	void move();

private:
	int degree;
	int radius;
	float dx = 0;
	float dy = 0;
	wxPoint position;
};

