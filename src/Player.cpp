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

	// 移動
	if (MoveDecision(joy.dwXpos&255, joy.dwYpos))
		position += m * Vec3f(StickValue(joy.dwXpos), 0.f, StickValue(joy.dwYpos))  * speed;
}

void Player::Draw() {
	// プレイヤー
	gl::pushModelView();
	gl::translate(position);
	gl::rotate(rotation);
	gl::color(Color(1.f, 1.f, 1.f));
	gl::drawColorCube(Vec3f(0.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f));
	gl::popModelView();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// デバッグ用
void Player::Debug() {
	console() << position << std::endl;
}