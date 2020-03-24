#pragma once

enum key_nav { 
	SHOOT = 32, 
	LEFT = 314, 
	UP = 315, 
	RIGHT = 316, 
	PAUSE = 112
};

struct asteroid_info_t {
	wxRealPoint pos;
	int radius;
};

