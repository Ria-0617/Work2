#include "TemplateProjectApp.h"

using namespace ci;
using namespace ci::app;

void TemplateProjectApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(800, 600);
}

void TemplateProjectApp::setup()
{
	joy1.SetUp();
	camera1.SetUp(getWindowWidth(),getWindowHeight());

	console() << player.GetPos() << std::endl;

	ui_camera = CameraOrtho(0.f, (float)getWindowWidth(), (float)getWindowHeight(), 0.f, -1.f, 1.f);
	ui_camera.setEyePoint(Vec3f(0.f, 0.f, 0.f));
	ui_camera.setCenterOfInterestPoint(Vec3f(0.f, 0.f, -1.f));

	gl::enableAlphaBlending();
	gl::enable(GL_COLOR_MATERIAL);

	joy1.SetUp();
}

void TemplateProjectApp::shutdown() {

}

void TemplateProjectApp::update()
{
	//joy1.Debug();

	

		// ‹Ê”­ŽË
	//if (joy1.joy.dwButtons == 0x0020) {    // 32
	//	Matrix44f m = Matrix44f::createRotation(ToRadians(playerRot));

	//	ball.position = playerPos;
	//	ball.v = m.transformVec(Vec3f(0.f, 0.f, 0.5f));
	//	ball.time = 10;
	//	balls.push_back(ball);
	//}

	//Ray ray(playerPos, Vec3f(0.f, -1.f, 0.f));
	//
	//float z;
	//if (ray.calcPlaneIntersection(Vec3f(0.f, -5.f, 0.f), Vec3f(0.f, 1.f, 0.f), &z)) {
	//	Vec3f p = ray.calcPosition(z);
	//	playerPos.y = p.y + 0.5f;
	//}
	//else {
	//	playerPos -= m * Vec3f(0.f, 0.01f, 0.f);
	//}

	camera1.UpDate(player.GetPos());
	player.UpDate(camera1.GetMatrix());

	console() << camera1.GetMatrix() << std::endl;
}

void TemplateProjectApp::draw()
{
#pragma region enable
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enable(GL_CULL_FACE);
	//gl::enable(GL_LIGHTING);
#pragma endregion
	// clear out the window with black
	gl::clear(Color(0, 0, 0));

	camera1.Draw();

	// templateField
#if 1
	for (int x = 0; x < 30; ++x) {
		for (int z = 0; z < 30; ++z) {
			color = x + z & 0x01 ? Color(0.f, 1.f, 1.f) : Color(0.f, 0.0f, 1.f);
			gl::color(color);
			gl::drawCube(Vec3f(0.f + x, -5.f, 0.f + z), Vec3f(1.f, 0.1f, 1.f));
		}
	}
#endif	

#pragma region Player
	player.Draw();
#pragma endregion

#pragma region disable
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	//gl::disable(GL_LIGHTING);
#pragma endregion

	gl::color(Color(1.f, 1.f, 1.f));
	gl::setMatrices(ui_camera);
}

CINDER_APP_NATIVE(TemplateProjectApp, RendererGl)