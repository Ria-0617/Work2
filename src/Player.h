#pragma once

#include "cinder/gl/gl.h"

#include "JoyController.h"
#include "Func.h"

#include <list>

class Player :public JoyController{
private:
	ci::Vec3f position;
	ci::Vec3f prevPosition;
	ci::Vec3f direction;
	float speed;

	const ci::Vec3f scale;
	const ci::Vec3f limitPositoin;

public:
	Player();

	ci::Vec3f GetPos() {
		return position;
	};

	void UpDate(ci::Matrix44f m);
	void Draw();
};
