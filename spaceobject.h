#pragma once
#include <ml5/ml5.h>

class spaceobject : public ml5::object {

public:
	spaceobject(wxPoint pos, int degree);
	virtual void move(wxSize size);
	void stay_in_universe(wxSize size);
	bool is_in_universe(wxSize size);
	double rad_of(int degree);

	wxPoint get_position() const {
		return position;
	}

	int get_degree() const {
		return degree;
	}

protected:

	float dx_speed = 0;
	float dy_speed = 0;

	wxPoint position;

	int degree;

};