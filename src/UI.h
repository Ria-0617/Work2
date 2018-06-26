#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder\Camera.h"

class UI {
	ci::CameraOrtho uiCamera;

	int score;

public:
	UI();

	void SetScore(int point) {
		score = point;
	}

	void SetUp(int, int);
	void UpDate();
	void Draw();
};
