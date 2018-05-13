#include "Player.h"

using namespace ci;
using namespace ci::app;

Player::Player() {
	position = Vec3f(0.f, 0.f, 0.f);
	prevPosition = position;
	direction = Vec3f(0.f, 0.f, 0.f);

	speed = 0.3f;
};

void Player::UpDate(Matrix44f m) {

	auto diff = position - prevPosition;
	if (diff != Vec3f(0.f, 0.f, 0.f)) {
		direction.y = atan2f(diff.x, diff.z) * 180.f / (float)M_PI;
		prevPosition = position;
	}

	// à⁄ìÆ
	if (MoveDecision(joy.dwXpos, joy.dwYpos))
		position += m * Vec3f(StickValue(joy.dwXpos), 0.f, StickValue(joy.dwYpos))  * speed;

	if (IsPressedButton(R1))
		shots.push_back(Shot(position));

	for (std::list<Shot>::iterator iter = shots.begin(); iter != shots.end();) {
		iter->UpDate(m);
		if (iter->isDead())
			iter = shots.erase(iter);
		else
			++iter;
	}
}

void Player::Draw() {
	// ÉvÉåÉCÉÑÅ[
	gl::pushModelView();
	gl::translate(position);
	gl::rotate(direction);
	gl::color(Color(1.f, 1.f, 1.f));
	gl::drawColorCube(Vec3f(0.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f));
	gl::popModelView();

	// ã 
	for (std::list<Shot>::iterator iter = shots.begin(); iter != shots.end(); ++iter) {
		iter->Draw();
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////