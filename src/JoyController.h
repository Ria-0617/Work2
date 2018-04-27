#pragma once

#pragma comment(lib,"winmm.lib")

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

class JoyController {
private:
	JOYINFOEX joy;

	ci::Vec3f leftStickValue;
	ci::Vec3f rightStickValue;

	float minValue;
	float maxValue;

public:
	JoyController();

	/*JOYINFOEX SetJoyInfo(JOYINFOEX joyInfo) {
		this->joy = joyInfo;
	}

	JoyController& operator=(const JoyController &obj) {
		joy = obj.joy;
		return *this;
	}*/

	JOYINFOEX GetJoyInfo() {
		return this->joy;
	};

	void SetUp();

	float StickValue(unsigned long value);
	bool MoveDecision(unsigned long valueX, unsigned long valueY);

	void Debug();
};
