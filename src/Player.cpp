#include "Player.h"

using namespace ci;
using namespace ci::app;

Player::Player() :scale(Vec3f(1.f, 1.f, 1.f)),limitPositoin(Vec3f(50.f, 50.f, 50.f)) {
	position = Vec3f(0.f, 0.f, 0.f);
	prevPosition = position;
	direction = Vec3f(0.f, 0.f, 0.f);

	speed = 0.3f;
};

void Player::UpDate(Matrix44f m) {

	auto diff = position - prevPosition;
	if (diff != Vec3f(0.f, 0.f, 0.f)) {
		direction.y = toDegrees(atan2f(diff.x, diff.z));
		prevPosition = position;
	}

	// à⁄ìÆ
	if (IsMove(/*minValue = */0.25f, joy.dwXpos, joy.dwYpos)) {
		position += m * Vec3f(StickValue(joy.dwXpos), 0.f, StickValue(joy.dwYpos))  * speed;

		position = MyFanc::Vec3fClamp(position, -limitPositoin, limitPositoin);
	}
}

void Player::Draw() {
	// ÉvÉåÉCÉÑÅ[
	gl::pushModelView();
	gl::translate(position);
	gl::rotate(direction);
	gl::color(Color(1.f, 1.f, 1.f));
	gl::drawColorCube(Vec3f(0.f, 0.f, 0.f), scale);
	gl::popModelView();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////