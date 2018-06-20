#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include <list>

class Boid {
	ci::Vec3f position;

	ci::Vec3f angle;
	ci::Vec3f direction;

	const float radius;
	

	const float viewAngleRange;
	const float viewDistanceRange;

	bool OutOfViewRange(Boid&, float, float);

	ci::Vec3f Separate(std::list<Boid>&);
	ci::Vec3f Alignment(std::list<Boid>&);
	ci::Vec3f Cohesion(std::list<Boid>&);

public:
	Boid();
	void Move(std::list<Boid>&);
	void MoveLimit();
	void Draw();
};
