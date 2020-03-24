#pragma once
#include <ml5/ml5.h>

class spaceobject : public ml5::object {

public:
	spaceobject(wxPoint pos, int degree);

	virtual void move(const wxSize &size) = 0;
	void stay_in_universe(const wxSize &size);
	bool is_in_universe(const wxSize &size);
	double rad_of(const int &degree);
	wxRealPoint get_position() const;
	int get_degree() const;
	void stop();
	void toggle_stop();

protected:
	
	int degree;
	float dx_speed = 0;
	float dy_speed = 0;
	wxRealPoint position;
	bool is_stopped{ false };

};