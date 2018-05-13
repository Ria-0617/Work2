#include "GameCamera.h"

using namespace ci;
using namespace ci::app;

GameCamera::GameCamera(Vec3f targetPos) {
	fov = 35.f;

	target = targetPos;
	offset = Vec3f(0.f, 0.f, -8.f);
	position = targetPos + offset;
	rotation = Vec3f(0.f, 0.f, 0.f);
	cameraCurrentPosition = position;
	rotationSpeed = 3.f;
};

void GameCamera::SetUp(int windowWidth, int windowHeight) {
	camera = CameraPersp(windowWidth, windowHeight, fov, 0.1f, 100.f);
	camera.setEyePoint(position);
	camera.setCenterOfInterestPoint(target);
}

void GameCamera::UpDate(Vec3f targetPos) {

	if (MoveDecision(joy.dwRpos, joy.dwZpos)) {
		rotation += Vec3f(StickValue(joy.dwRpos), StickValue(joy.dwZpos), 0.f)*rotationSpeed;

		matrix = Matrix44f::createRotation(ToRadians(rotation));

		console() << matrix << std::endl;
	}

	cameraCurrentPosition = targetPos + matrix * offset;
	Vec3f t = targetPos + matrix * Vec3f(0.f, 0.f, 2.f);

	camera.setEyePoint(cameraCurrentPosition + Vec3f(0.f, 5.f, 0.f));
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