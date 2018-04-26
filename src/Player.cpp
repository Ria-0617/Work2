#include "Player.h"

using namespace ci;
using namespace ci::app;

Player::Player() {
	position = Vec3f(0.f, 0.f, 0.f);
	prevPosition = position;
	rotation = Vec3f(0.f, 0.f, 0.f);

	speed = 0.3f;
};

void Player::UpDate(Matrix44f m) {
	
	auto diff = position - prevPosition;
	if (diff != Vec3f(0.f, 0.f, 0.f)) {
		rotation.y = atan2f(diff.x, diff.z) * 180.f / (float)M_PI;
		prevPosition = position;
	}

	// �ړ�
	if (joy1.MoveDecision(joy1.GetJoyInfo().dwXpos, joy1.GetJoyInfo().dwYpos))
		position += m * Vec3f(joy1.StickValue(joy1.GetJoyInfo().dwXpos), 0.f, joy1.StickValue(joy1.GetJoyInfo().dwYpos))  * speed;
}

void Player::Draw() {
	// �v���C���[
	gl::pushModelView();
	gl::translate(position);
	gl::rotate(rotation);
	gl::color(Color(1.f, 1.f, 1.f));
	gl::drawColorCube(Vec3f(0.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f));
	gl::popModelView();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �f�o�b�O�p
void Player::Debug() {
	console() << position << std::endl;
}