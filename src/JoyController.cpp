#include "JoyController.h"

using namespace ci;
using namespace ci::app;

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
	return 1 - 2.f*value / maxValue;
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
		console() << "L_Xpos = " << (maxValue / 2.f - GetJoyInfo().dwXpos) / (maxValue * 5.f) << std::endl;
		console() << "L_Ypos = " << maxValue / 2.0 - GetJoyInfo().dwYpos << std::endl;
		console() << "R_posX = " << GetJoyInfo().dwZpos - maxValue / 2.0 << std::endl;     // 右スティック横
		console() << "R_posY = " << maxValue / 2.0 - GetJoyInfo().dwRpos << std::endl;    // 右スティック縦
		console() << "R2 = " << GetJoyInfo().dwUpos << std::endl;    // R2
		console() << "L2 = " << GetJoyInfo().dwVpos << std::endl;    // L2
		console() << "Buttons = " << GetJoyInfo().dwButtons << std::endl;
	}
	else {
		console() << "エラー" << std::endl;
	}
}