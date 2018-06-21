#include "Boid.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Boid::Boid() :radius(1.f), viewAngleRange(toRadians(45.f)), viewDistanceRange(5.f) {
	position = Vec3f(randFloat(-50.f, 50.f), randFloat(-50.f, 50.f), randFloat(-50.f, 50.f));

	angle = MyFanc::ToRadians(Vec3f(0, 0, randFloat(0.f, 360.f)));
	direction = Matrix44f::createRotation(angle) * Vec3f(0.f, 1.f, 0.f);
}

bool Boid::OutOfViewRange(Boid& boid, float viewAngleRange, float viewDistanceRange) {
	Vec3f neighbors = (boid.position - position).normalized();

	if (direction.dot(neighbors) < viewAngleRange || position.distance(boid.position) > viewDistanceRange) {
		return true;
	}
	return false;
}

Vec3f Boid::Separate(list<Boid>&boids) {
	Vec3f relativePosition = Vec3f(0, 0, 0);
	Vec3f toAgent;

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		if (position.distance(itr->position) > viewDistanceRange) continue;
		//if (OutOfViewRange(*itr, viewAngleRange, viewDistanceRange))continue;

		toAgent = (position - itr->position).safeNormalized();

		relativePosition += toAgent;
	}

	return relativePosition;
}

Vec3f Boid::Alignment(list<Boid>&boids) {
	int neiborCount = 0;
	Vec3f ralativeAngle = Vec3f(0, 0, 0);

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		if (OutOfViewRange(*itr, viewAngleRange, viewDistanceRange))continue;

		ralativeAngle += itr->angle;

		++neiborCount;
	}

	if (neiborCount > 0) {
		ralativeAngle /= neiborCount;
	}

	angle = ralativeAngle;
	direction = Matrix44f::createRotation(angle) * Vec3f(0.f, 1.f, 0.f);

	return direction;
}


Vec3f Boid::Cohesion(list<Boid>&boids) {
	Vec3f centerPos = Vec3f(0, 0, 0);

	int neiborCount = 0;

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		if (OutOfViewRange(*itr, viewAngleRange, viewDistanceRange))continue;

		centerPos += itr->position;
		++neiborCount;
	}
	
	if (neiborCount > 0) {
		centerPos /= neiborCount;
	}

	return (centerPos - position).safeNormalized();
}

void Boid::Move(list<Boid>& boids) {
	Vec3f v;
	v = position;
	v += Separate(boids);
	v += Alignment(boids);
	v += Cohesion(boids);

	position += ((v - position) * 0.3f);
}

void Boid::MoveLimit() {
	if (position.x > 50)
		position.x -= 100;
	if (position.x < -50)
		position.x += 100;

	if (position.y > 50)
		position.y -= 100;
	if (position.y < -50)
		position.y += 100;

	if (position.z > 50)
		position.z -= 100;
	if (position.z < -50)
		position.z += 100;
}

void Boid::Draw() {
	gl::drawSphere(position, radius);
	gl::drawLine(position, position + direction * 10);
}