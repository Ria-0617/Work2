#include "Shot.h"

using namespace ci;
using namespace ci::app;

Shot::Shot(ci::Vec3f playerPos) {
	position = playerPos;
	radius = 0.2f;
	speed = 3.f;
	surviveTime = 10;
}

void Shot::UpDate(Matrix44f m) {
	position += m * Vec3f(0.f, 0.f, 1.f) * speed;

	surviveTime -= 1;
}

void Shot::Draw() {
	gl::drawSphere(position, radius);
}

bool Shot::isDead() {
	return surviveTime <= 0;
}

