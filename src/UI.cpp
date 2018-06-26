#include "UI.h"

using namespace ci;
using namespace ci::app;

UI::UI() {
	score = 0;
}

void UI::SetUp(int windowWidth, int windowHeight) {
	uiCamera = CameraOrtho(0.f, windowWidth, windowHeight, 0.f, -1.f, 1.f);
	uiCamera.setEyePoint(Vec3f(0.f, 0.f, 0.f));
	uiCamera.setCenterOfInterestPoint(Vec3f(0.f, 0.f, -1.f));
}

void UI::UpDate() {

}

void UI::Draw() {
	gl::color(Color(1.f, 1.f, 1.f));
	gl::setMatrices(uiCamera);
}