#include "appl.h"
#include "types.h"

#define INTERVAL 1000000 //0
#define RAND_RADIUS rand() % 40
#define RAND_DEGREE rand() % 360
#define INITIAL_ASTEROIDS 20
#define SPACESHIP_SIZE 40

/* GENERAL =============================================*/
auto draw_application::make_window() const->std::unique_ptr<ml5::window> { 
	return std::make_unique<window>();
}

draw_application::window::window() : ml5::window{"ML5.Asteroids"} {	
	set_prop_initial_size({1200,900});
}

draw_application::window::~window(){
	bullet_container.clear();
	asteroid_container.clear();
}

/* INIT ================================================*/
void draw_application::window::on_init() {
	set_prop_background_brush(*wxBLACK_BRUSH);
	ml5::duration_t time(INTERVAL);
	start_timer(time);
	create_asteroids_rand(INITIAL_ASTEROIDS);
	spaceship.set_center(get_size());
}

/* CALL DRAW FUNCTIONS =================================*/
void draw_application::window::on_paint(const ml5::paint_event& event) {
	auto& con{ event.get_context() };
	for (auto& a : asteroid_container) a->draw(con);
	for (auto& b : bullet_container) b->draw(con);
	spaceship.draw(con);
	status.draw(con);
	if(!status.is_game_over()) 
		set_status_text("HIT COUNT: " + std::to_string(status.get_hit_counter()));
	else 
		set_status_text("**GAME OVER** HIT COUNT: " + std::to_string(status.get_hit_counter()));
}

/* PAUSE ===============================================*/
void draw_application::window::pause() {
	if (status.is_game_over()) return;
	for (auto& a : asteroid_container) a->toggle_stop();
	for (auto& b : bullet_container) b->toggle_stop();
	spaceship.toggle_stop();
}

/* REACT ON KEY EVENT ==================================*/
void draw_application::window::on_key(ml5::key_event const& event) {
	switch (event.get_key_code())
	{

	case key_nav::SHOOT:	create_bullet();					break;
	case key_nav::LEFT:		spaceship.rotate_left(); 			break;
	case key_nav::UP:		spaceship.boost(get_size());		break;
	case key_nav::RIGHT:	spaceship.rotate_right();			break;
	case key_nav::PAUSE:	pause();							break;

	default:	std::cout << "wrong key..." << std::endl;
	}
	refresh();
}

/* CREATE NEW BULLET ===================================*/
void draw_application::window::create_bullet() {
	 wxPoint bullet_position = {
		wxPoint(spaceship.get_position()).x + SPACESHIP_SIZE/2, 
		wxPoint(spaceship.get_position()).y + SPACESHIP_SIZE/2 
	};
	bullet_container.add(std::make_shared<bullet>(bullet_position, spaceship.get_degree()));
}

/* CREATE NEW RAND ASTEROIDS ===========================*/
void draw_application::window::create_asteroids_rand(int cnt) {
	wxPoint asteroid_position;
	for (int i = 0; i < cnt; i++) {
		asteroid_position = { 
			rand() % get_size().x,
			rand() % get_size().y 
		};
		asteroid_container.add(std::make_shared<asteroid>(wxPoint(asteroid_position), RAND_RADIUS, RAND_DEGREE));
	}
}

/* CREATE NEW ASTEROIDS ================================*/
void draw_application::window::create_asteroids(wxRealPoint asteroid_position, int radius, int cnt) {
	for (int i = 0; i < cnt; i++) {
		asteroid_container.add(std::make_shared<asteroid>(wxPoint(asteroid_position), radius, RAND_DEGREE));
	}
}

/* COLLISION BULLET ASTEROID ===========================*/
void draw_application::window::check_bullet_asteroid() {
	wxRealPoint new_asteroid_pos;
	int new_asteroid_radius;
	for (auto& b : bullet_container) {
		wxRealPoint pos{ b->get_position() };
		std::shared_ptr<asteroid> to_delete{ nullptr };
		for (auto& a : asteroid_container) {
			if (a->was_hit(pos)) {
				to_delete = a;
				new_asteroid_pos = a->get_position();
				new_asteroid_radius = a->get_radius();
				status.increase_hit_counter();
			}
		}

		if (to_delete) {
			if (new_asteroid_radius >= 20)  
				create_asteroids(new_asteroid_pos, new_asteroid_radius / 2, 2);
			asteroid_container.remove(to_delete);
		}
	}
}

/* REMOVE BULLET FROM UNIVERSE ==========================*/
void draw_application::window::remove_bullets() {
	std::shared_ptr<bullet> bullet_to_delete{ nullptr };
	for (auto& b : bullet_container) {
		if (!b->is_in_universe(get_size())) {
			bullet_to_delete = b;
		}
	}
	if(bullet_to_delete) bullet_container.remove(bullet_to_delete);
}

/* COLLISION SPACESHIP ASTEROID =========================*/
void draw_application::window::check_spaceship_asteroid() {
	for (auto& b : asteroid_container) {
		if (spaceship.crashed(b->get_region())) {
			spaceship.set_center(get_size());
			status.decrease_life_counter();
			if (status.get_life_counter() == 0) spaceship.stop();
		}
	}
}

/* COLLISION DETECTION ==================================*/
void draw_application::window::collision_detection() {
	check_bullet_asteroid();
	check_spaceship_asteroid();
	remove_bullets();
}

/* UPDATE GAME STATE ===================================*/
void draw_application::window::on_timer(const ml5::timer_event& event) {
	wxPoint asteroid_position = { rand() % get_size().x,rand() % get_size().y };
	create_asteroids(asteroid_position, 40, INITIAL_ASTEROIDS - asteroid_container.size());
	for (auto &a : asteroid_container) a->move(get_size());
	for (auto &b : bullet_container) b->move(get_size());
	collision_detection();
	spaceship.move(get_size());
	refresh();
}

/* ON RESIZE ===========================================*/
void draw_application::window::on_size(const ml5::size_event & event) {
	if(status.is_game_over()) spaceship.set_center(get_size());
}
