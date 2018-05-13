#pragma once

#include "cinder/gl/gl.h"
#include "JoyController.h"

#include "Shot.h"
#include <list>

class Player :public JoyController{
private:
	ci::Vec3f position;
	ci::Vec3f prevPosition;
	ci::Vec3f direction;
	float speed;

	std::list<Shot> shots;

public:
	Player();

	ci::Vec3f GetPos() {
		return this->position;
	};

	void UpDate(ci::Matrix44f m);
	void Draw();
};
