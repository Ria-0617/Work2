#include "JoyController.h"

using namespace ci;
using namespace ci::app;

JoyController::JoyController() {
	leftStickValue = Vec3f(0.f, 0.f, 0.f);
	rightStickValue = Vec3f(0.f, 0.f, 0.f);

	minValue = 0.25f;
	maxValue = 3452816845.f;
}

void JoyController::SetUp() {

	joy.dwSize = sizeof JOYINFOEX;
	joy.dwFlags = JOY_RETURNALL;

	// ゲームパッドが接続しているか確認
	for (unsigned int i = 0; i < joyGetNumDevs(); ++i) {    //サポートされているジョイスティックの数を返す
		if (JOYERR_NOERROR == joyGetPosEx(i, &GetJoyInfo()))
			console() << i << std::endl;
	}
}

// 正規化
float JoyController::StickValue(unsigned long value) {
	return 1 - 2 * value / maxValue;
}

bool JoyController::MoveDecision(unsigned long valueX, unsigned long valueY) {
	//0番のジョイスティックの情報を見る
	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &GetJoyInfo())) {
		if (StickValue(valueX) > minValue || StickValue(valueX) < -minValue ||
			StickValue(valueY) > minValue || StickValue(valueY) < -minValue)
			return true;
		else
			return false;
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// デバッグ用
// ボタン確認
void JoyController::Debug() {
	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &GetJoyInfo())) { //0番のジョイスティックの情報を見る
		console() << "L_posX = " << StickValue(GetJoyInfo().dwXpos) << std::endl;
		console() << "L_posY = " << StickValue(GetJoyInfo().dwYpos) << std::endl;
		console() << "R_posX = " << StickValue(GetJoyInfo().dwZpos) << std::endl;     // 右スティック横
		console() << "R_posY = " << StickValue(joy.dwRpos) << std::endl;    // 右スティック縦
		console() << "R2 = " << GetJoyInfo().dwUpos << std::endl;    // R2
		console() << "L2 = " << GetJoyInfo().dwVpos << std::endl;    // L2
		console() << "Buttons = " << GetJoyInfo().dwButtons << std::endl;
		console() << ' ' << std::endl;
	}
	else {
		console() << "エラー" << std::endl;
	}
}