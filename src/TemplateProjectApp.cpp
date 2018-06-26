#include "TemplateProjectApp.h"

using namespace ci;
using namespace ci::app;

void TemplateProjectApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(800, 600);
}

void TemplateProjectApp::setup()
{
	camera1.SetUp(getWindowWidth(), getWindowHeight());

	for (int i = 1; i < 50; ++i) {
		boids.push_back(Boid());
	}

	uiCamera.SetUp(getWindowWidth(), getWindowHeight());

	gl::enableAlphaBlending();
	gl::enable(GL_COLOR_MATERIAL);
}

void TemplateProjectApp::shutdown() {

}

void TemplateProjectApp::update()
{
	camera1.UpDate(player.GetPos());
	player.UpDate(camera1.GetMatrix());

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		itr->Move(boids);
		itr->MoveLimit();
	}


	if (IsPressedButton(R1)) {
		shotTime += 1;
		if (shotTime % 5 == 0)
			bullets.push_back(Bullet(player.GetPos(), camera1.GetMatrix()));
	}
	else
		shotTime = 0;

	for (auto itr = bullets.begin(); itr != bullets.end();) {
		itr->UpDate();
		if (itr->isDead())
			itr = bullets.erase(itr);
		else
			++itr;

		// ‹Ê‚Æ“G‚Ì“–‚½‚è”»’è
		for (auto itr2 = boids.begin(); itr2 != boids.end(); ++itr2) {
			if (MyFanc::CircleCollider(itr->GetPosition(), itr->GetRadius(), itr2->GetPosition(), itr2->GetRadius())) {
				itr = bullets.erase(itr);
				if (boids.size() > enemyMaxNum)continue;
				boids.push_back(Boid(itr2->GetPosition()));
			}
		}
	}
	//console() << camera1.GetMatrix() << std::endl;
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

	player.Draw();

	// ‹Ê
	for (auto itr = bullets.begin(); itr != bullets.end(); ++itr) {
		itr->Draw();
	}

	for (auto itr = boids.begin(); itr != boids.end(); ++itr) {
		itr->Draw();
	}

#pragma region disable
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	//gl::disable(GL_LIGHTING);
#pragma endregion

	uiCamera.Draw();
}

CINDER_APP_NATIVE(TemplateProjectApp, RendererGl)