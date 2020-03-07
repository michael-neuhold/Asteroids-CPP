#include "asteroids.h"
#include <cmath>

asteroids::asteroids(wxPoint pos, int radius)
	:	position{ pos }, 
		radius{radius},
		degree{ rand() % 360 }
{}

asteroids::~asteroids() {

}

void asteroids::draw(context& con) {
	con.DrawCircle(position, radius);
}

void asteroids::move() {
	dx = sin(degree * M_PI/180) * 2;
	dy = -cos(degree * M_PI / 180) * 2;
	
	std::cout << "dx = " << dx << " | dy = " << dy << std::endl;
	
	position.x += dx;
	position.y += dy;
}