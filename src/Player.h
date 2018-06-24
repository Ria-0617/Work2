#pragma once

#include "cinder/gl/gl.h"

<<<<<<< HEAD
#include "JoyController.h"
#include "Shot.h"

=======
>>>>>>> 978f49d8fb066a14215cfe808229b64f42e40f43
#include <list>

class Player :public JoyController{
private:
	ci::Vec3f position;
	ci::Vec3f prevPosition;
	ci::Vec3f direction;
	float speed;

	const ci::Vec3f scale;
public:
	Player();

	ci::Vec3f GetPos() {
		return position;
	};

	void UpDate(ci::Matrix44f m);
	void Draw();
};
