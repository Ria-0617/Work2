#include "JoyController.h"

using namespace ci;
using namespace ci::app;

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
	return 1 - 2.f*value / maxValue;
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
		console() << "L_Xpos = " << (maxValue / 2.f - GetJoyInfo().dwXpos) / (maxValue * 5.f) << std::endl;
		console() << "L_Ypos = " << maxValue / 2.0 - GetJoyInfo().dwYpos << std::endl;
		console() << "R_posX = " << GetJoyInfo().dwZpos - maxValue / 2.0 << std::endl;     // �E�X�e�B�b�N��
		console() << "R_posY = " << maxValue / 2.0 - GetJoyInfo().dwRpos << std::endl;    // �E�X�e�B�b�N�c
		console() << "R2 = " << GetJoyInfo().dwUpos << std::endl;    // R2
		console() << "L2 = " << GetJoyInfo().dwVpos << std::endl;    // L2
		console() << "Buttons = " << GetJoyInfo().dwButtons << std::endl;
	}
	else {
		console() << "�G���[" << std::endl;
	}
}