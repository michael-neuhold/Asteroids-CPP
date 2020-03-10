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

	/* movements */
	void rotate_left();
	void rotate_right();
	void boost(wxSize size);

	/* position */
	void set_center(wxSize size);
	void move(wxSize size) override;

	/* crash */
	bool crashed(wxRegion asteroid);

	/* game over */
	void stop_spaceship();

private:

	/* spaceship image */
	wxImage original_spaceship_image;
	wxImage spaceship_image;

	/* size X = Y */
	int spaceship_size = 40;	

	// drifting
	int prev_degree;

	// TODO: create sound object
	// sound
	// wxSound fire(R"(C:\\Users\\michaelneuhold\\Desktop\\fire.wav)");

	// game over
	bool stop{ false };

};

