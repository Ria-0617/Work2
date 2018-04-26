#include "GameCamera.h"

using namespace ci;
using namespace ci::app;

GameCamera::GameCamera(Vec3f pos) {
	fov = 35.f;

	target = pos;
	position = pos + Vec3f(0.f, 0.f, -8.f);
	cameraCurrentPosition = position;
	rotation = Vec3f(0.f, 0.f, 0.f);
	rotationSpeed = 3.f;

	matrix = 0;
};

void GameCamera::SetUp(int windowWidth, int windowHeight) {
	camera = CameraPersp(windowWidth, windowHeight, fov, 0.1f, 100.f);
	camera.setEyePoint(position);
	camera.setCenterOfInterestPoint(target);
}

void GameCamera::UpDate(Vec3f target) {

	if (joy1.MoveDecision(joy1.GetJoyInfo().dwRpos, joy1.GetJoyInfo().dwZpos)) {
		rotation += Vec3f(0.f, joy1.StickValue(joy1.GetJoyInfo().dwZpos), 0.f)*rotationSpeed;

		matrix = Matrix44f::createRotation(ToRadians(rotation));
	}

	target = target + matrix * (position - GameCamera::target);
	Vec3f t = target + matrix * Vec3f(0.f, 0.f, 2.f);

	camera.setEyePoint(target + Vec3f(0.f, 5.f, 0.f));
	camera.setCenterOfInterestPoint(t + Vec3f(0.f, 1.f, 0.f));
}

void GameCamera::Draw() {
	gl::setMatrices(camera);
}

Vec3f ToRadians(const Vec3f& degrees) {
	return degrees * M_PI / 180.f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Debug—p

void GameCamera::Debug() {

}