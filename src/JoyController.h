#pragma once

#pragma comment(lib,"winmm.lib")

#include "cinder/app/AppNative.h"

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

class JoyController {
private:
	const float maxValue;

protected:
	JOYINFOEX joy;

	enum Buttons {
		rect = 1,
		cross = 2,
		circle = 4,
		triangle = 8,
		L1 = 16,
		R1 = 32
	};

public:
	JoyController();

	void SetUp();

	float StickValue(unsigned long value);
	bool IsMove(float minValue, unsigned long valueX, unsigned long valueY);
	bool IsPressedButton(unsigned long buttonNum);

	void Debug();
};
