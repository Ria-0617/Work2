#pragma once

#include "cinder/gl/gl.h"
#include "JoyController.h"

class Player {
private:
	ci::Vec3f position;
	ci::Vec3f prevPosition;
	ci::Vec3f rotation;
	float speed;

	JoyController joy1;
public:
	Player();

	ci::Vec3f GetPos() {
		return this->position;
	};

	void UpDate(ci::Matrix44f m);
	void Draw();

	void Debug();
};
