#include "deadbeefgl.h"
#include "ship.h"

DeadbeefGL::DeadbeefGL(int x, int y, int w, int h, const char* l) : GlWindow(x, y, w, h, l) {
	std::istringstream in(ship_obj);
	ship = new Object(in);
	std::shared_ptr<Shader> base(std::make_shared<Shader>(nullptr, nullptr));
	ship->setShader(0, base);
}

void DeadbeefGL::initialize() {
	ship->initialize();
}

void DeadbeefGL::glDraw(const mat4& projection, const mat4& view, float time) {
	ship->draw(projection, view, time);
}