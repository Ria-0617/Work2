#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

class Shot {
private:
	ci::Vec3f position;
	ci::Matrix44f direction;
	float radius;
	float speed;
	int surviveTime;

public:
	Shot(ci::Vec3f playerPos);


	void UpDate(ci::Matrix44f m);
	void Draw();
	bool isDead();
};
