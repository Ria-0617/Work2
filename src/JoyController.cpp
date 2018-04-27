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

	// �Q�[���p�b�h���ڑ����Ă��邩�m�F
	for (unsigned int i = 0; i < joyGetNumDevs(); ++i) {    //�T�|�[�g����Ă���W���C�X�e�B�b�N�̐���Ԃ�
		if (JOYERR_NOERROR == joyGetPosEx(i, &GetJoyInfo()))
			console() << i << std::endl;
	}
}

// ���K��
float JoyController::StickValue(unsigned long value) {
	return 1 - 2 * value / maxValue;
}

bool JoyController::MoveDecision(unsigned long valueX, unsigned long valueY) {
	//0�Ԃ̃W���C�X�e�B�b�N�̏�������
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

// �f�o�b�O�p
// �{�^���m�F
void JoyController::Debug() {
	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &GetJoyInfo())) { //0�Ԃ̃W���C�X�e�B�b�N�̏�������
		console() << "L_posX = " << StickValue(GetJoyInfo().dwXpos) << std::endl;
		console() << "L_posY = " << StickValue(GetJoyInfo().dwYpos) << std::endl;
		console() << "R_posX = " << StickValue(GetJoyInfo().dwZpos) << std::endl;     // �E�X�e�B�b�N��
		console() << "R_posY = " << StickValue(joy.dwRpos) << std::endl;    // �E�X�e�B�b�N�c
		console() << "R2 = " << GetJoyInfo().dwUpos << std::endl;    // R2
		console() << "L2 = " << GetJoyInfo().dwVpos << std::endl;    // L2
		console() << "Buttons = " << GetJoyInfo().dwButtons << std::endl;
		console() << ' ' << std::endl;
	}
	else {
		console() << "�G���[" << std::endl;
	}
}