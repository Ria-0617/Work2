#pragma once

#pragma comment(lib,"winmm.lib")

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

class JoyController {
private:
	float minValue;
	float maxValue;

protected:
	JOYINFOEX joy;

public:
	JoyController();

	/*JOYINFOEX SetJoyInfo(JOYINFOEX joyInfo) {
		this->joy = joyInfo;
	}

	JoyController& operator=(const JoyController &obj) {
		joy = obj.joy;
		return *this;
	}*/

	void SetUp();

	float StickValue(unsigned long value);
	bool MoveDecision(unsigned long valueX, unsigned long valueY);

	void Debug();
};
